#include "iqjs_handles.h"

#include <string>
#include <unordered_map>

using namespace iqjs;

namespace {

struct BeatmapCollector {
    JSContext* ctx{};
    JSValue native{ JS_UNDEFINED };
    JSValue mil{ JS_UNDEFINED };
    JSValue meta{ JS_UNDEFINED };
    JSValue bpms{ JS_UNDEFINED };
    JSValue lines{ JS_UNDEFINED };
    JSValue storyboard_objects{ JS_UNDEFINED };
    JSValue animations{ JS_UNDEFINED };
    std::int64_t note_index{};
};

std::unordered_map<JSContext*, BeatmapCollector*>& collector_registry()
{
    static std::unordered_map<JSContext*, BeatmapCollector*> value;
    return value;
}

std::unordered_map<JSRuntime*, JSClassID>& beatmap_class_ids()
{
    static std::unordered_map<JSRuntime*, JSClassID> value;
    return value;
}

std::string json_escape(std::string_view value)
{
    static constexpr char hex[] = "0123456789abcdef";
    std::string output;
    output.reserve(value.size() + 2);
    output.push_back('"');
    for (unsigned char c : value) {
        switch (c) {
        case '"': output += "\\\""; break;
        case '\\': output += "\\\\"; break;
        case '\b': output += "\\b"; break;
        case '\f': output += "\\f"; break;
        case '\n': output += "\\n"; break;
        case '\r': output += "\\r"; break;
        case '\t': output += "\\t"; break;
        default:
            if (c < 0x20) {
                output += "\\u00";
                output.push_back(hex[c >> 4]);
                output.push_back(hex[c & 15]);
            } else {
                output.push_back(static_cast<char>(c));
            }
        }
    }
    output.push_back('"');
    return output;
}

std::string value_string(JSContext* ctx, JSValueConst value)
{
    JSValue string = JS_ToString(ctx, value);
    if (JS_IsException(string)) return {};
    size_t length = 0;
    const char* text = JS_ToCStringLen(ctx, &length, string);
    std::string output = text ? std::string(text, length) : std::string{};
    if (text) JS_FreeCString(ctx, text);
    JS_FreeValue(ctx, string);
    return output;
}

std::string exception_json(JSContext* ctx, std::string_view fallback)
{
    std::string message(fallback);
    std::string stack;
    if (JS_HasException(ctx)) {
        JSValue exception = JS_GetException(ctx);
        message = value_string(ctx, exception);
        if (JS_IsObject(exception)) {
            JSValue stack_value = JS_GetPropertyStr(ctx, exception, "stack");
            if (!JS_IsException(stack_value) && !JS_IsUndefined(stack_value))
                stack = value_string(ctx, stack_value);
            JS_FreeValue(ctx, stack_value);
        }
        JS_FreeValue(ctx, exception);
    }
    return "{\"error\":" + json_escape(message) + ",\"stack\":" + json_escape(stack) + "}";
}

BeatmapCollector* current_collector(JSContext* ctx)
{
    auto it = collector_registry().find(ctx);
    return it == collector_registry().end() ? nullptr : it->second;
}

JSValue missing_collector(JSContext* ctx)
{
    return JS_ThrowTypeError(ctx, "MilizeBeatmap collector is not active");
}

int set(JSContext* ctx, JSValueConst object, const char* name, JSValue value)
{
    return JS_SetPropertyStr(ctx, object, name, value);
}

int append(JSContext* ctx, JSValueConst array, JSValue value)
{
    std::int64_t length = 0;
    if (JS_GetLength(ctx, array, &length) < 0 || length < 0 || length > UINT32_MAX) {
        JS_FreeValue(ctx, value);
        return -1;
    }
    return JS_SetPropertyUint32(ctx, array, static_cast<std::uint32_t>(length), value);
}

JSValue argument(JSContext* ctx, int argc, JSValueConst* argv, int index)
{
    return index < argc ? JS_DupValue(ctx, argv[index]) : JS_UNDEFINED;
}

JSValue timing(JSContext* ctx, JSValueConst, int argc, JSValueConst* argv)
{
    BeatmapCollector* collector = current_collector(ctx);
    if (!collector) return missing_collector(ctx);
    if (argc < 3) return JS_ThrowTypeError(ctx, "timing requires start, bpm and beatsPerBar");
    JSValue record = JS_NewObject(ctx);
    if (JS_IsException(record)) return record;
    if (set(ctx, record, "start", argument(ctx, argc, argv, 0)) < 0 ||
        set(ctx, record, "bpm", argument(ctx, argc, argv, 1)) < 0 ||
        set(ctx, record, "beatsPerBar", argument(ctx, argc, argv, 2)) < 0 ||
        append(ctx, collector->bpms, record) < 0) {
        return JS_EXCEPTION;
    }
    std::int64_t length = 0;
    if (JS_GetLength(ctx, collector->bpms, &length) < 0) return JS_EXCEPTION;
    return JS_NewInt64(ctx, length - 1);
}

JSValue line(JSContext* ctx, JSValueConst, int, JSValueConst*)
{
    BeatmapCollector* collector = current_collector(ctx);
    if (!collector) return missing_collector(ctx);
    JSValue record = JS_NewObject(ctx);
    if (JS_IsException(record)) return record;
    if (set(ctx, record, "notes", JS_NewArray(ctx)) < 0 || append(ctx, collector->lines, record) < 0)
        return JS_EXCEPTION;
    std::int64_t length = 0;
    if (JS_GetLength(ctx, collector->lines, &length) < 0) return JS_EXCEPTION;
    return JS_NewInt64(ctx, length - 1);
}

JSValue note(JSContext* ctx, JSValueConst, int argc, JSValueConst* argv)
{
    BeatmapCollector* collector = current_collector(ctx);
    if (!collector) return missing_collector(ctx);
    if (argc < 7) return JS_ThrowTypeError(ctx, "note requires seven arguments");
    std::int32_t line_index = -1;
    if (JS_ToInt32(ctx, &line_index, argv[0]) < 0 || line_index < 0)
        return JS_ThrowTypeError(ctx, "note line must be a valid non-negative index");
    JSValue line_record = JS_GetPropertyUint32(ctx, collector->lines, static_cast<std::uint32_t>(line_index));
    if (JS_IsException(line_record)) return line_record;
    if (!JS_IsObject(line_record)) {
        JS_FreeValue(ctx, line_record);
        return JS_ThrowTypeError(ctx, "note references a line that does not exist");
    }
    JSValue notes = JS_GetPropertyStr(ctx, line_record, "notes");
    JS_FreeValue(ctx, line_record);
    if (JS_IsException(notes)) return notes;
    JSValue record = JS_NewObject(ctx);
    if (JS_IsException(record)) { JS_FreeValue(ctx, notes); return record; }
    const char* names[] = { "bpm", "startTime", "endTime", "type", "isFake", "isAlwaysPerfect" };
    for (int i = 0; i < 6; ++i) {
        if (set(ctx, record, names[i], argument(ctx, argc, argv, i + 1)) < 0) {
            JS_FreeValue(ctx, notes);
            JS_FreeValue(ctx, record);
            return JS_EXCEPTION;
        }
    }
    const std::int64_t index = collector->note_index++;
    if (set(ctx, record, "index", JS_NewInt64(ctx, index)) < 0 || append(ctx, notes, record) < 0) {
        JS_FreeValue(ctx, notes);
        return JS_EXCEPTION;
    }
    JS_FreeValue(ctx, notes);
    return JS_NewInt64(ctx, index);
}

JSValue animation(JSContext* ctx, JSValueConst, int argc, JSValueConst* argv)
{
    BeatmapCollector* collector = current_collector(ctx);
    if (!collector) return missing_collector(ctx);
    if (argc < 12) return JS_ThrowTypeError(ctx, "animation requires twelve arguments");
    static constexpr const char* names[] = {
        "bpmId", "fromBeat", "toBeat", "key", "fv", "tv", "data", "i1",
        "press", "ease", "valueExpression", "customEaseExpression"
    };
    JSValue record = JS_NewObject(ctx);
    if (JS_IsException(record)) return record;
    for (int i = 0; i < 12; ++i) {
        if (set(ctx, record, names[i], argument(ctx, argc, argv, i)) < 0) {
            JS_FreeValue(ctx, record);
            return JS_EXCEPTION;
        }
    }
    if (append(ctx, collector->animations, record) < 0) return JS_EXCEPTION;
    return JS_UNDEFINED;
}

JSValue with_property(JSContext* ctx, JSValueConst, int argc, JSValueConst* argv)
{
    BeatmapCollector* collector = current_collector(ctx);
    if (!collector) return missing_collector(ctx);
    if (argc < 2) return JS_ThrowTypeError(ctx, "withProperty requires a key and value");
    JSAtom key = JS_ValueToAtom(ctx, argv[0]);
    if (key == JS_ATOM_NULL) return JS_EXCEPTION;
    int status = JS_SetProperty(ctx, collector->meta, key, JS_DupValue(ctx, argv[1]));
    JS_FreeAtom(ctx, key);
    return status < 0 ? JS_EXCEPTION : JS_DupValue(ctx, collector->native);
}

void native_finalizer(JSRuntime*, JSValueConst) {}

bool initialize_collector(BeatmapCollector& collector)
{
    JSContext* ctx = collector.ctx;
    JSRuntime* rt = JS_GetRuntime(ctx);
    auto class_entry = beatmap_class_ids().find(rt);
    JSClassID class_id = class_entry == beatmap_class_ids().end()
        ? JS_INVALID_CLASS_ID
        : class_entry->second;
    if (class_id == JS_INVALID_CLASS_ID) {
        JS_NewClassID(rt, &class_id);
        JSClassDef definition{};
        definition.class_name = "MilizeBeatmap";
        definition.finalizer = native_finalizer;
        if (JS_NewClass(rt, class_id, &definition) < 0) return false;
        beatmap_class_ids().emplace(rt, class_id);
    }
    collector.native = JS_NewObjectClass(ctx, class_id);
    collector.mil = JS_NewObject(ctx);
    collector.meta = JS_NewObject(ctx);
    collector.bpms = JS_NewArray(ctx);
    collector.lines = JS_NewArray(ctx);
    collector.storyboard_objects = JS_NewArray(ctx);
    collector.animations = JS_NewArray(ctx);
    if (JS_IsException(collector.native) || JS_IsException(collector.mil) ||
        JS_IsException(collector.meta) || JS_IsException(collector.bpms) ||
        JS_IsException(collector.lines) || JS_IsException(collector.storyboard_objects) ||
        JS_IsException(collector.animations)) return false;
    if (JS_SetOpaque(collector.native, &collector) < 0) return false;
    if (set(ctx, collector.mil, "meta", JS_DupValue(ctx, collector.meta)) < 0 ||
        set(ctx, collector.mil, "bpms", JS_DupValue(ctx, collector.bpms)) < 0 ||
        set(ctx, collector.mil, "lines", JS_DupValue(ctx, collector.lines)) < 0 ||
        set(ctx, collector.mil, "storyboardObjects", JS_DupValue(ctx, collector.storyboard_objects)) < 0 ||
        set(ctx, collector.mil, "animations", JS_DupValue(ctx, collector.animations)) < 0 ||
        set(ctx, collector.native, "mil", JS_DupValue(ctx, collector.mil)) < 0)
        return false;
    JSValue timing_fn = JS_NewCFunction(ctx, timing, "timing", 3);
    JSValue note_fn = JS_NewCFunction(ctx, note, "note", 7);
    JSValue animation_fn = JS_NewCFunction(ctx, animation, "animation", 12);
    JSValue property_fn = JS_NewCFunction(ctx, with_property, "withProperty", 2);
    JSValue line_fn = JS_NewCFunction(ctx, line, "line", 0);
    if (JS_IsException(timing_fn) || JS_IsException(note_fn) || JS_IsException(animation_fn) ||
        JS_IsException(property_fn) || JS_IsException(line_fn)) {
        JS_FreeValue(ctx, timing_fn);
        JS_FreeValue(ctx, note_fn);
        JS_FreeValue(ctx, animation_fn);
        JS_FreeValue(ctx, property_fn);
        JS_FreeValue(ctx, line_fn);
        return false;
    }
    return set(ctx, collector.native, "timing", timing_fn) >= 0 &&
           set(ctx, collector.native, "note", note_fn) >= 0 &&
           set(ctx, collector.native, "animation", animation_fn) >= 0 &&
           set(ctx, collector.native, "withProperty", JS_DupValue(ctx, property_fn)) >= 0 &&
           set(ctx, collector.native, "p", property_fn) >= 0 &&
           set(ctx, collector.native, "line", line_fn) >= 0;
}

void free_collector(BeatmapCollector& collector)
{
    JS_SetOpaque(collector.native, nullptr);
    JS_FreeValue(collector.ctx, collector.native);
    JS_FreeValue(collector.ctx, collector.mil);
    JS_FreeValue(collector.ctx, collector.meta);
    JS_FreeValue(collector.ctx, collector.bpms);
    JS_FreeValue(collector.ctx, collector.lines);
    JS_FreeValue(collector.ctx, collector.storyboard_objects);
    JS_FreeValue(collector.ctx, collector.animations);
}

} // namespace

std::string iqjs_beatmap_eval(std::uint64_t ctx_h, std::string_view source,
                              std::string_view filename)
{
    std::lock_guard<TableMutex> lock(table_mutex());
    JSContext* ctx = ctx_of(ctx_h);
    if (!ctx) return "{\"error\":\"invalid QuickJS context handle\",\"stack\":\"\"}";
    if (collector_registry().find(ctx) != collector_registry().end())
        return "{\"error\":\"MilizeBeatmap evaluation is already active in this context\",\"stack\":\"\"}";

    BeatmapCollector collector;
    collector.ctx = ctx;
    if (!initialize_collector(collector)) {
        std::string error = exception_json(ctx, "failed to initialize MilizeBeatmap");
        free_collector(collector);
        return error;
    }

    JSValue global = JS_GetGlobalObject(ctx);
    JSAtom atom = JS_NewAtom(ctx, "MilizeBeatmap");
    if (JS_IsException(global) || atom == JS_ATOM_NULL) {
        std::string error = exception_json(ctx, "failed to access global object");
        if (atom != JS_ATOM_NULL) JS_FreeAtom(ctx, atom);
        JS_FreeValue(ctx, global);
        free_collector(collector);
        return error;
    }
    int had_previous = JS_HasProperty(ctx, global, atom);
    JSValue previous = had_previous > 0 ? JS_GetProperty(ctx, global, atom) : JS_UNDEFINED;
    if (had_previous < 0 || JS_IsException(previous) ||
        JS_SetProperty(ctx, global, atom, JS_DupValue(ctx, collector.native)) < 0) {
        std::string error = exception_json(ctx, "failed to install MilizeBeatmap");
        JS_FreeValue(ctx, previous);
        JS_FreeValue(ctx, global);
        JS_FreeAtom(ctx, atom);
        free_collector(collector);
        return error;
    }

    collector_registry()[ctx] = &collector;
    std::string file(filename.empty() ? "<beatmap>" : filename);
    JSValue eval_result = JS_Eval(ctx, source.data(), source.size(), file.c_str(), JS_EVAL_TYPE_GLOBAL);
    collector_registry().erase(ctx);
    if (had_previous > 0) JS_SetProperty(ctx, global, atom, previous);
    else { JS_DeleteProperty(ctx, global, atom, 0); JS_FreeValue(ctx, previous); }
    JS_FreeAtom(ctx, atom);
    JS_FreeValue(ctx, global);

    if (JS_IsException(eval_result)) {
        std::string error = exception_json(ctx, "beatmap evaluation failed");
        free_collector(collector);
        return error;
    }
    JS_FreeValue(ctx, eval_result);
    JSValue json = JS_JSONStringify(ctx, collector.mil, JS_UNDEFINED, JS_UNDEFINED);
    if (JS_IsException(json)) {
        std::string error = exception_json(ctx, "failed to serialize beatmap");
        free_collector(collector);
        return error;
    }
    size_t length = 0;
    const char* text = JS_ToCStringLen(ctx, &length, json);
    if (!text) {
        JS_FreeValue(ctx, json);
        std::string error = exception_json(ctx, "failed to encode beatmap JSON");
        free_collector(collector);
        return error;
    }
    std::string output(text, length);
    JS_FreeCString(ctx, text);
    JS_FreeValue(ctx, json);
    free_collector(collector);
    return output;
}
