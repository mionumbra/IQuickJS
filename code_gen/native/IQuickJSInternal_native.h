// ##### extgen :: Auto-generated file do not edit!! #####

#pragma once
#include <cstdint>
#include <string_view>
#include <vector>
#include <array>
#include <optional>
#include "core/GMExtWire.h"

namespace gm_consts
{
}


namespace gm_enums
{
    enum class IQJSValueTag : std::int64_t
    {
        BigInt = -9,
        Symbol = -8,
        String = -7,
        StringRope = -6,
        Module = -3,
        FunctionBytecode = -2,
        Object = -1,
        Int = 0,
        Bool = 1,
        Null = 2,
        Undefined = 3,
        Uninitialized = 4,
        CatchOffset = 5,
        Exception = 6,
        ShortBigInt = 7,
        Float64 = 8
    };

    enum class IQJSEvalFlags : std::int64_t
    {
        Global = 0,
        Module = 1,
        Direct = 2,
        Indirect = 3,
        TypeMask = 3,
        Strict = 8,
        CompileOnly = 32,
        BacktraceBarrier = 64,
        Async = 128
    };

    enum class IQJSPropertyFlags : std::int64_t
    {
        Configurable = 1,
        Writable = 2,
        Enumerable = 4,
        CWE = 7,
        HasConfigurable = 256,
        HasWritable = 512,
        HasEnumerable = 1024,
        HasGet = 2048,
        HasSet = 4096,
        HasValue = 8192,
        Throw = 16384,
        ThrowStrict = 32768
    };

    enum class IQJSGPNFlags : std::int64_t
    {
        StringMask = 1,
        SymbolMask = 2,
        PrivateMask = 4,
        EnumOnly = 16,
        SetEnum = 32
    };

    enum class IQJSWriteObjectFlags : std::int64_t
    {
        Bytecode = 1,
        BSwap = 0,
        SharedArrayBuffer = 4,
        Reference = 8,
        StripSource = 16,
        StripDebug = 32
    };

    enum class IQJSReadObjectFlags : std::int64_t
    {
        Bytecode = 1,
        RomData = 0,
        SharedArrayBuffer = 4,
        Reference = 8
    };

    enum class IQJSTypedArrayType : std::int64_t
    {
        Uint8Clamped = 0,
        Int8 = 1,
        Uint8 = 2,
        Int16 = 3,
        Uint16 = 4,
        Int32 = 5,
        Uint32 = 6,
        BigInt64 = 7,
        BigUint64 = 8,
        Float16 = 9,
        Float32 = 10,
        Float64 = 11
    };

    enum class IQJSPromiseState : std::int64_t
    {
        NotAPromise = -1,
        Pending = 0,
        Fulfilled = 1,
        Rejected = 2
    };

    enum class IQJSPromiseHookType : std::int64_t
    {
        Init = 0,
        Before = 1,
        After = 2,
        Resolve = 3
    };

    enum class IQJSDumpFlags : std::uint64_t
    {
        BytecodeFinal = 1,
        BytecodePass2 = 2,
        BytecodePass1 = 4,
        BytecodeHex = 16,
        BytecodePC2Line = 32,
        BytecodeStack = 64,
        BytecodeStep = 128,
        ReadObject = 256,
        Free = 512,
        GC = 1024,
        GCFree = 2048,
        ModuleResolve = 4096,
        Promise = 8192,
        Leaks = 16384,
        AtomLeaks = 32768,
        Memory = 65536,
        Objects = 131072,
        Atoms = 262144,
        Shapes = 524288,
        AbortOnLeaks = 1097728
    };

}


namespace gm_structs
{
    struct IQJSMemoryUsage;
    struct IQJSInt32Result;
    struct IQJSUInt32Result;
    struct IQJSInt64Result;
    struct IQJSUInt64Result;
    struct IQJSFloatResult;
    struct IQJSReallocResult;
    struct IQJSPropertyEnumEntry;
    struct IQJSPropertyDescriptorResult;
    struct IQJSTypedArrayBufferInfo;
    struct IQJSJobResult;
    struct IQJSPromiseCapability;
    struct IQJSOpaqueResult;
    struct IQJSEvalOptions;
    struct IQJSFunctionListEntry;
    struct IQJSSerializedObject;

    struct IQJSMemoryUsage
    {
        std::int64_t malloc_size;
        std::int64_t malloc_limit;
        std::int64_t memory_used_size;
        std::int64_t malloc_count;
        std::int64_t memory_used_count;
        std::int64_t atom_count;
        std::int64_t atom_size;
        std::int64_t str_count;
        std::int64_t str_size;
        std::int64_t obj_count;
        std::int64_t obj_size;
        std::int64_t prop_count;
        std::int64_t prop_size;
        std::int64_t shape_count;
        std::int64_t shape_size;
        std::int64_t js_func_count;
        std::int64_t js_func_size;
        std::int64_t js_func_code_size;
        std::int64_t js_func_pc2line_count;
        std::int64_t js_func_pc2line_size;
        std::int64_t c_func_count;
        std::int64_t array_count;
        std::int64_t fast_array_count;
        std::int64_t fast_array_elements;
        std::int64_t binary_object_count;
        std::int64_t binary_object_size;
    };

    struct IQJSInt32Result
    {
        std::int32_t status;
        std::int32_t value;
    };

    struct IQJSUInt32Result
    {
        std::int32_t status;
        std::uint32_t value;
    };

    struct IQJSInt64Result
    {
        std::int32_t status;
        std::int64_t value;
    };

    struct IQJSUInt64Result
    {
        std::int32_t status;
        std::uint64_t value;
    };

    struct IQJSFloatResult
    {
        std::int32_t status;
        float value;
    };

    struct IQJSReallocResult
    {
        std::uint64_t pointer;
        std::uint64_t slack;
    };

    struct IQJSPropertyEnumEntry
    {
        bool is_enumerable;
        std::uint64_t atom;
    };

    struct IQJSPropertyDescriptorResult
    {
        std::int32_t status;
        std::int32_t flags;
        std::uint64_t value;
        std::uint64_t getter;
        std::uint64_t setter;
    };

    struct IQJSTypedArrayBufferInfo
    {
        std::uint64_t buffer;
        std::uint64_t byte_offset;
        std::uint64_t byte_length;
        std::uint64_t bytes_per_element;
    };

    struct IQJSJobResult
    {
        std::int32_t status;
        std::uint64_t context;
    };

    struct IQJSPromiseCapability
    {
        std::uint64_t promise;
        std::uint64_t resolve;
        std::uint64_t reject;
    };

    struct IQJSOpaqueResult
    {
        std::uint64_t pointer;
        std::uint64_t class_id;
    };

    struct IQJSEvalOptions
    {
        std::int32_t version;
        gm_enums::IQJSEvalFlags eval_flags;
        std::string filename;
        std::int32_t line_num;
    };

    struct IQJSFunctionListEntry
    {
        std::string name;
        std::int32_t definition_type;
        std::int32_t property_flags;
        std::string string_value;
        std::int64_t integer_value;
        float float_value;
        std::uint64_t value;
    };

    struct IQJSSerializedObject
    {
        std::vector<std::uint8_t> bytes;
        std::vector<std::uint64_t> shared_array_buffer_pointers;
    };

}

namespace gm::wire::codec
{
    template<>
    inline void writeValue<gm_structs::IQJSMemoryUsage>(gm::byteio::IByteWriter& _buf, const gm_structs::IQJSMemoryUsage& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.malloc_size);
        gm::wire::codec::writeValue(_buf, obj.malloc_limit);
        gm::wire::codec::writeValue(_buf, obj.memory_used_size);
        gm::wire::codec::writeValue(_buf, obj.malloc_count);
        gm::wire::codec::writeValue(_buf, obj.memory_used_count);
        gm::wire::codec::writeValue(_buf, obj.atom_count);
        gm::wire::codec::writeValue(_buf, obj.atom_size);
        gm::wire::codec::writeValue(_buf, obj.str_count);
        gm::wire::codec::writeValue(_buf, obj.str_size);
        gm::wire::codec::writeValue(_buf, obj.obj_count);
        gm::wire::codec::writeValue(_buf, obj.obj_size);
        gm::wire::codec::writeValue(_buf, obj.prop_count);
        gm::wire::codec::writeValue(_buf, obj.prop_size);
        gm::wire::codec::writeValue(_buf, obj.shape_count);
        gm::wire::codec::writeValue(_buf, obj.shape_size);
        gm::wire::codec::writeValue(_buf, obj.js_func_count);
        gm::wire::codec::writeValue(_buf, obj.js_func_size);
        gm::wire::codec::writeValue(_buf, obj.js_func_code_size);
        gm::wire::codec::writeValue(_buf, obj.js_func_pc2line_count);
        gm::wire::codec::writeValue(_buf, obj.js_func_pc2line_size);
        gm::wire::codec::writeValue(_buf, obj.c_func_count);
        gm::wire::codec::writeValue(_buf, obj.array_count);
        gm::wire::codec::writeValue(_buf, obj.fast_array_count);
        gm::wire::codec::writeValue(_buf, obj.fast_array_elements);
        gm::wire::codec::writeValue(_buf, obj.binary_object_count);
        gm::wire::codec::writeValue(_buf, obj.binary_object_size);
    }

    template<>
    inline gm_structs::IQJSMemoryUsage readValue<gm_structs::IQJSMemoryUsage>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::IQJSMemoryUsage obj;
        obj.malloc_size = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.malloc_limit = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.memory_used_size = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.malloc_count = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.memory_used_count = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.atom_count = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.atom_size = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.str_count = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.str_size = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.obj_count = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.obj_size = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.prop_count = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.prop_size = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.shape_count = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.shape_size = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.js_func_count = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.js_func_size = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.js_func_code_size = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.js_func_pc2line_count = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.js_func_pc2line_size = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.c_func_count = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.array_count = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.fast_array_count = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.fast_array_elements = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.binary_object_count = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.binary_object_size = gm::wire::codec::readValue<std::int64_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::IQJSInt32Result>(gm::byteio::IByteWriter& _buf, const gm_structs::IQJSInt32Result& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.status);
        gm::wire::codec::writeValue(_buf, obj.value);
    }

    template<>
    inline gm_structs::IQJSInt32Result readValue<gm_structs::IQJSInt32Result>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::IQJSInt32Result obj;
        obj.status = gm::wire::codec::readValue<std::int32_t>(_buf);
        obj.value = gm::wire::codec::readValue<std::int32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::IQJSUInt32Result>(gm::byteio::IByteWriter& _buf, const gm_structs::IQJSUInt32Result& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.status);
        gm::wire::codec::writeValue(_buf, obj.value);
    }

    template<>
    inline gm_structs::IQJSUInt32Result readValue<gm_structs::IQJSUInt32Result>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::IQJSUInt32Result obj;
        obj.status = gm::wire::codec::readValue<std::int32_t>(_buf);
        obj.value = gm::wire::codec::readValue<std::uint32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::IQJSInt64Result>(gm::byteio::IByteWriter& _buf, const gm_structs::IQJSInt64Result& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.status);
        gm::wire::codec::writeValue(_buf, obj.value);
    }

    template<>
    inline gm_structs::IQJSInt64Result readValue<gm_structs::IQJSInt64Result>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::IQJSInt64Result obj;
        obj.status = gm::wire::codec::readValue<std::int32_t>(_buf);
        obj.value = gm::wire::codec::readValue<std::int64_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::IQJSUInt64Result>(gm::byteio::IByteWriter& _buf, const gm_structs::IQJSUInt64Result& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.status);
        gm::wire::codec::writeValue(_buf, obj.value);
    }

    template<>
    inline gm_structs::IQJSUInt64Result readValue<gm_structs::IQJSUInt64Result>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::IQJSUInt64Result obj;
        obj.status = gm::wire::codec::readValue<std::int32_t>(_buf);
        obj.value = gm::wire::codec::readValue<std::uint64_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::IQJSFloatResult>(gm::byteio::IByteWriter& _buf, const gm_structs::IQJSFloatResult& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.status);
        gm::wire::codec::writeValue(_buf, obj.value);
    }

    template<>
    inline gm_structs::IQJSFloatResult readValue<gm_structs::IQJSFloatResult>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::IQJSFloatResult obj;
        obj.status = gm::wire::codec::readValue<std::int32_t>(_buf);
        obj.value = gm::wire::codec::readValue<float>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::IQJSReallocResult>(gm::byteio::IByteWriter& _buf, const gm_structs::IQJSReallocResult& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.pointer);
        gm::wire::codec::writeValue(_buf, obj.slack);
    }

    template<>
    inline gm_structs::IQJSReallocResult readValue<gm_structs::IQJSReallocResult>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::IQJSReallocResult obj;
        obj.pointer = gm::wire::codec::readValue<std::uint64_t>(_buf);
        obj.slack = gm::wire::codec::readValue<std::uint64_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::IQJSPropertyEnumEntry>(gm::byteio::IByteWriter& _buf, const gm_structs::IQJSPropertyEnumEntry& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.is_enumerable);
        gm::wire::codec::writeValue(_buf, obj.atom);
    }

    template<>
    inline gm_structs::IQJSPropertyEnumEntry readValue<gm_structs::IQJSPropertyEnumEntry>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::IQJSPropertyEnumEntry obj;
        obj.is_enumerable = gm::wire::codec::readValue<bool>(_buf);
        obj.atom = gm::wire::codec::readValue<std::uint64_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::IQJSPropertyDescriptorResult>(gm::byteio::IByteWriter& _buf, const gm_structs::IQJSPropertyDescriptorResult& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.status);
        gm::wire::codec::writeValue(_buf, obj.flags);
        gm::wire::codec::writeValue(_buf, obj.value);
        gm::wire::codec::writeValue(_buf, obj.getter);
        gm::wire::codec::writeValue(_buf, obj.setter);
    }

    template<>
    inline gm_structs::IQJSPropertyDescriptorResult readValue<gm_structs::IQJSPropertyDescriptorResult>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::IQJSPropertyDescriptorResult obj;
        obj.status = gm::wire::codec::readValue<std::int32_t>(_buf);
        obj.flags = gm::wire::codec::readValue<std::int32_t>(_buf);
        obj.value = gm::wire::codec::readValue<std::uint64_t>(_buf);
        obj.getter = gm::wire::codec::readValue<std::uint64_t>(_buf);
        obj.setter = gm::wire::codec::readValue<std::uint64_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::IQJSTypedArrayBufferInfo>(gm::byteio::IByteWriter& _buf, const gm_structs::IQJSTypedArrayBufferInfo& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.buffer);
        gm::wire::codec::writeValue(_buf, obj.byte_offset);
        gm::wire::codec::writeValue(_buf, obj.byte_length);
        gm::wire::codec::writeValue(_buf, obj.bytes_per_element);
    }

    template<>
    inline gm_structs::IQJSTypedArrayBufferInfo readValue<gm_structs::IQJSTypedArrayBufferInfo>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::IQJSTypedArrayBufferInfo obj;
        obj.buffer = gm::wire::codec::readValue<std::uint64_t>(_buf);
        obj.byte_offset = gm::wire::codec::readValue<std::uint64_t>(_buf);
        obj.byte_length = gm::wire::codec::readValue<std::uint64_t>(_buf);
        obj.bytes_per_element = gm::wire::codec::readValue<std::uint64_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::IQJSJobResult>(gm::byteio::IByteWriter& _buf, const gm_structs::IQJSJobResult& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.status);
        gm::wire::codec::writeValue(_buf, obj.context);
    }

    template<>
    inline gm_structs::IQJSJobResult readValue<gm_structs::IQJSJobResult>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::IQJSJobResult obj;
        obj.status = gm::wire::codec::readValue<std::int32_t>(_buf);
        obj.context = gm::wire::codec::readValue<std::uint64_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::IQJSPromiseCapability>(gm::byteio::IByteWriter& _buf, const gm_structs::IQJSPromiseCapability& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.promise);
        gm::wire::codec::writeValue(_buf, obj.resolve);
        gm::wire::codec::writeValue(_buf, obj.reject);
    }

    template<>
    inline gm_structs::IQJSPromiseCapability readValue<gm_structs::IQJSPromiseCapability>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::IQJSPromiseCapability obj;
        obj.promise = gm::wire::codec::readValue<std::uint64_t>(_buf);
        obj.resolve = gm::wire::codec::readValue<std::uint64_t>(_buf);
        obj.reject = gm::wire::codec::readValue<std::uint64_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::IQJSOpaqueResult>(gm::byteio::IByteWriter& _buf, const gm_structs::IQJSOpaqueResult& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.pointer);
        gm::wire::codec::writeValue(_buf, obj.class_id);
    }

    template<>
    inline gm_structs::IQJSOpaqueResult readValue<gm_structs::IQJSOpaqueResult>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::IQJSOpaqueResult obj;
        obj.pointer = gm::wire::codec::readValue<std::uint64_t>(_buf);
        obj.class_id = gm::wire::codec::readValue<std::uint64_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::IQJSEvalOptions>(gm::byteio::IByteWriter& _buf, const gm_structs::IQJSEvalOptions& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.version);
        gm::wire::codec::writeValue(_buf, obj.eval_flags);
        gm::wire::codec::writeValue(_buf, obj.filename);
        gm::wire::codec::writeValue(_buf, obj.line_num);
    }

    template<>
    inline gm_structs::IQJSEvalOptions readValue<gm_structs::IQJSEvalOptions>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::IQJSEvalOptions obj;
        obj.version = gm::wire::codec::readValue<std::int32_t>(_buf);
        obj.eval_flags = gm::wire::codec::readValue<gm_enums::IQJSEvalFlags>(_buf);
        obj.filename = gm::wire::codec::readValue<std::string>(_buf);
        obj.line_num = gm::wire::codec::readValue<std::int32_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::IQJSFunctionListEntry>(gm::byteio::IByteWriter& _buf, const gm_structs::IQJSFunctionListEntry& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.name);
        gm::wire::codec::writeValue(_buf, obj.definition_type);
        gm::wire::codec::writeValue(_buf, obj.property_flags);
        gm::wire::codec::writeValue(_buf, obj.string_value);
        gm::wire::codec::writeValue(_buf, obj.integer_value);
        gm::wire::codec::writeValue(_buf, obj.float_value);
        gm::wire::codec::writeValue(_buf, obj.value);
    }

    template<>
    inline gm_structs::IQJSFunctionListEntry readValue<gm_structs::IQJSFunctionListEntry>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::IQJSFunctionListEntry obj;
        obj.name = gm::wire::codec::readValue<std::string>(_buf);
        obj.definition_type = gm::wire::codec::readValue<std::int32_t>(_buf);
        obj.property_flags = gm::wire::codec::readValue<std::int32_t>(_buf);
        obj.string_value = gm::wire::codec::readValue<std::string>(_buf);
        obj.integer_value = gm::wire::codec::readValue<std::int64_t>(_buf);
        obj.float_value = gm::wire::codec::readValue<float>(_buf);
        obj.value = gm::wire::codec::readValue<std::uint64_t>(_buf);
        return obj;
    }

    template<>
    inline void writeValue<gm_structs::IQJSSerializedObject>(gm::byteio::IByteWriter& _buf, const gm_structs::IQJSSerializedObject& obj)
    {
        gm::wire::codec::writeValue(_buf, obj.bytes);
        gm::wire::codec::writeValue(_buf, obj.shared_array_buffer_pointers);
    }

    template<>
    inline gm_structs::IQJSSerializedObject readValue<gm_structs::IQJSSerializedObject>(gm::byteio::BufferReader& _buf)
    {
        gm_structs::IQJSSerializedObject obj;
        obj.bytes = gm::wire::codec::readVector<std::uint8_t>(_buf);
        obj.shared_array_buffer_pointers = gm::wire::codec::readVector<std::uint64_t>(_buf);
        return obj;
    }

}

namespace gm::wire::details
{
    template<>
    struct gm_struct_traits<gm_structs::IQJSMemoryUsage>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 0;
    };

    template<>
    struct gm_struct_traits<gm_structs::IQJSInt32Result>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 1;
    };

    template<>
    struct gm_struct_traits<gm_structs::IQJSUInt32Result>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 2;
    };

    template<>
    struct gm_struct_traits<gm_structs::IQJSInt64Result>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 3;
    };

    template<>
    struct gm_struct_traits<gm_structs::IQJSUInt64Result>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 4;
    };

    template<>
    struct gm_struct_traits<gm_structs::IQJSFloatResult>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 5;
    };

    template<>
    struct gm_struct_traits<gm_structs::IQJSReallocResult>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 6;
    };

    template<>
    struct gm_struct_traits<gm_structs::IQJSPropertyEnumEntry>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 7;
    };

    template<>
    struct gm_struct_traits<gm_structs::IQJSPropertyDescriptorResult>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 8;
    };

    template<>
    struct gm_struct_traits<gm_structs::IQJSTypedArrayBufferInfo>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 9;
    };

    template<>
    struct gm_struct_traits<gm_structs::IQJSJobResult>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 10;
    };

    template<>
    struct gm_struct_traits<gm_structs::IQJSPromiseCapability>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 11;
    };

    template<>
    struct gm_struct_traits<gm_structs::IQJSOpaqueResult>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 12;
    };

    template<>
    struct gm_struct_traits<gm_structs::IQJSEvalOptions>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 13;
    };

    template<>
    struct gm_struct_traits<gm_structs::IQJSFunctionListEntry>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 14;
    };

    template<>
    struct gm_struct_traits<gm_structs::IQJSSerializedObject>
    {
        static constexpr bool is_gm_struct = true;
        static constexpr std::uint32_t codec_id = 15;
    };

}

void iqjs_init();
void iqjs_shutdown();
std::uint64_t iqjs_new_runtime();
std::uint64_t iqjs_unsafe_new_runtime_with_allocator(std::string_view policy, std::uint64_t opaque);
void iqjs_free_runtime(std::uint64_t rt);
void iqjs_set_runtime_info(std::uint64_t rt, std::string_view info);
void iqjs_set_dump_flags(std::uint64_t rt, gm_enums::IQJSDumpFlags flags);
std::uint64_t iqjs_get_dump_flags(std::uint64_t rt);
void iqjs_update_stack_top(std::uint64_t rt);
void iqjs_run_gc(std::uint64_t rt);
bool iqjs_is_live_object(std::uint64_t rt, std::uint64_t value);
void iqjs_set_can_block(std::uint64_t rt, bool can_block);
bool iqjs_is_job_pending(std::uint64_t rt);
std::uint64_t iqjs_get_pending_job_context(std::uint64_t rt);
gm_structs::IQJSJobResult iqjs_execute_pending_job(std::uint64_t rt);
std::string iqjs_get_version();
void iqjs_unsafe_set_runtime_opaque(std::uint64_t rt, std::uint64_t pointer);
std::uint64_t iqjs_unsafe_get_runtime_opaque(std::uint64_t rt);
std::uint64_t iqjs_add_runtime_finalizer_adapter(std::uint64_t rt, const gm::wire::GMFunction& callback, std::uint64_t arg);
void iqjs_remove_runtime_finalizer_adapter(std::uint64_t registration);
void iqjs_mark_value_adapter(std::uint64_t rt, std::uint64_t value);
std::uint64_t iqjs_new_context(std::uint64_t rt);
std::uint64_t iqjs_new_context_raw(std::uint64_t rt);
std::uint64_t iqjs_dup_context(std::uint64_t ctx);
void iqjs_free_context(std::uint64_t ctx);
std::uint64_t iqjs_get_runtime(std::uint64_t ctx);
void iqjs_unsafe_set_context_opaque(std::uint64_t ctx, std::uint64_t pointer);
std::uint64_t iqjs_unsafe_get_context_opaque(std::uint64_t ctx);
std::uint64_t iqjs_get_function_proto(std::uint64_t ctx);
std::int32_t iqjs_add_intrinsic_base_objects(std::uint64_t ctx);
std::int32_t iqjs_add_intrinsic_date(std::uint64_t ctx);
std::int32_t iqjs_add_intrinsic_eval(std::uint64_t ctx);
void iqjs_add_intrinsic_regexp_compiler(std::uint64_t ctx);
std::int32_t iqjs_add_intrinsic_regexp(std::uint64_t ctx);
std::int32_t iqjs_add_intrinsic_json(std::uint64_t ctx);
std::int32_t iqjs_add_intrinsic_proxy(std::uint64_t ctx);
std::int32_t iqjs_add_intrinsic_map_set(std::uint64_t ctx);
std::int32_t iqjs_add_intrinsic_typed_arrays(std::uint64_t ctx);
std::int32_t iqjs_add_intrinsic_promise(std::uint64_t ctx);
std::int32_t iqjs_add_intrinsic_bigint(std::uint64_t ctx);
std::int32_t iqjs_add_intrinsic_weak_ref(std::uint64_t ctx);
std::int32_t iqjs_add_performance(std::uint64_t ctx);
std::int32_t iqjs_add_intrinsic_dom_exception(std::uint64_t ctx);
std::int32_t iqjs_add_intrinsic_atob(std::uint64_t ctx);
void iqjs_set_memory_limit(std::uint64_t rt, std::uint64_t limit);
std::uint64_t iqjs_get_gc_threshold(std::uint64_t rt);
void iqjs_set_gc_threshold(std::uint64_t rt, std::uint64_t threshold);
void iqjs_set_max_stack_size(std::uint64_t rt, std::uint64_t size);
gm_structs::IQJSMemoryUsage iqjs_compute_memory_usage(std::uint64_t rt);
std::string iqjs_dump_memory_usage(std::uint64_t rt);
std::uint64_t iqjs_unsafe_calloc_rt(std::uint64_t rt, std::uint64_t count, std::uint64_t size);
std::uint64_t iqjs_unsafe_malloc_rt(std::uint64_t rt, std::uint64_t size);
std::uint64_t iqjs_unsafe_mallocz_rt(std::uint64_t rt, std::uint64_t size);
std::uint64_t iqjs_unsafe_realloc_rt(std::uint64_t rt, std::uint64_t pointer, std::uint64_t size);
void iqjs_unsafe_free_rt(std::uint64_t rt, std::uint64_t pointer);
std::uint64_t iqjs_unsafe_malloc_usable_size_rt(std::uint64_t rt, std::uint64_t pointer);
std::uint64_t iqjs_unsafe_calloc(std::uint64_t ctx, std::uint64_t count, std::uint64_t size);
std::uint64_t iqjs_unsafe_malloc(std::uint64_t ctx, std::uint64_t size);
std::uint64_t iqjs_unsafe_mallocz(std::uint64_t ctx, std::uint64_t size);
std::uint64_t iqjs_unsafe_realloc(std::uint64_t ctx, std::uint64_t pointer, std::uint64_t size);
gm_structs::IQJSReallocResult iqjs_unsafe_realloc2(std::uint64_t ctx, std::uint64_t pointer, std::uint64_t size);
void iqjs_unsafe_free(std::uint64_t ctx, std::uint64_t pointer);
std::uint64_t iqjs_unsafe_malloc_usable_size(std::uint64_t ctx, std::uint64_t pointer);
std::uint64_t iqjs_unsafe_strdup(std::uint64_t ctx, std::string_view value);
std::uint64_t iqjs_unsafe_strndup(std::uint64_t ctx, std::string_view value, std::uint64_t byte_count);
std::uint64_t iqjs_atom_null();
std::uint64_t iqjs_new_atom(std::uint64_t ctx, std::string_view value);
std::uint64_t iqjs_new_atom_len(std::uint64_t ctx, std::string_view value, std::uint64_t byte_count);
std::uint64_t iqjs_new_atom_uint32(std::uint64_t ctx, std::uint32_t value);
std::uint64_t iqjs_dup_atom(std::uint64_t ctx, std::uint64_t atom);
std::uint64_t iqjs_dup_atom_rt(std::uint64_t rt, std::uint64_t atom);
void iqjs_free_atom(std::uint64_t ctx, std::uint64_t atom);
void iqjs_free_atom_rt(std::uint64_t rt, std::uint64_t atom);
std::uint64_t iqjs_atom_to_value(std::uint64_t ctx, std::uint64_t atom);
std::uint64_t iqjs_atom_to_string(std::uint64_t ctx, std::uint64_t atom);
std::string iqjs_atom_to_cstring(std::uint64_t ctx, std::uint64_t atom);
std::uint64_t iqjs_value_to_atom(std::uint64_t ctx, std::uint64_t value);
std::uint64_t iqjs_new_class_id(std::uint64_t rt);
std::uint64_t iqjs_get_class_id(std::uint64_t value);
std::int32_t iqjs_new_class_adapter(std::uint64_t rt, std::uint64_t class_id, std::string_view name, const gm::wire::GMFunction& finalizer, const gm::wire::GMFunction& gc_mark, const gm::wire::GMFunction& call);
bool iqjs_is_registered_class(std::uint64_t rt, std::uint64_t class_id);
std::uint64_t iqjs_get_class_name(std::uint64_t rt, std::uint64_t class_id);
void iqjs_set_class_proto(std::uint64_t ctx, std::uint64_t class_id, std::uint64_t proto);
std::uint64_t iqjs_get_class_proto(std::uint64_t ctx, std::uint64_t class_id);
std::int32_t iqjs_set_class_exotic_adapter(std::uint64_t ctx, std::uint64_t class_id, std::uint64_t methods_object);
std::uint64_t iqjs_null(std::uint64_t ctx);
std::uint64_t iqjs_undefined(std::uint64_t ctx);
std::uint64_t iqjs_true(std::uint64_t ctx);
std::uint64_t iqjs_false(std::uint64_t ctx);
std::uint64_t iqjs_exception(std::uint64_t ctx);
std::uint64_t iqjs_uninitialized(std::uint64_t ctx);
std::uint64_t iqjs_new_bool(std::uint64_t ctx, bool value);
std::uint64_t iqjs_new_int32(std::uint64_t ctx, std::int32_t value);
std::uint64_t iqjs_new_int64(std::uint64_t ctx, std::int64_t value);
std::uint64_t iqjs_new_uint32(std::uint64_t ctx, std::uint32_t value);
std::uint64_t iqjs_new_uint64(std::uint64_t ctx, std::uint64_t value);
std::uint64_t iqjs_new_float64(std::uint64_t ctx, float value);
std::uint64_t iqjs_new_number(std::uint64_t ctx, float value);
std::uint64_t iqjs_new_bigint64(std::uint64_t ctx, std::int64_t value);
std::uint64_t iqjs_new_biguint64(std::uint64_t ctx, std::uint64_t value);
std::uint64_t iqjs_new_catch_offset(std::uint64_t ctx, std::int32_t value);
std::uint64_t iqjs_new_string(std::uint64_t ctx, std::string_view value);
std::uint64_t iqjs_new_string_len(std::uint64_t ctx, std::string_view value, std::uint64_t byte_count);
std::uint64_t iqjs_new_string_utf16(std::uint64_t ctx, const std::vector<std::uint16_t>& code_units);
std::uint64_t iqjs_new_atom_string(std::uint64_t ctx, std::string_view value);
std::uint64_t iqjs_new_symbol(std::uint64_t ctx, std::string_view description, bool is_global);
void iqjs_free_value(std::uint64_t ctx, std::uint64_t value);
void iqjs_free_value_rt(std::uint64_t rt, std::uint64_t value);
std::uint64_t iqjs_dup_value(std::uint64_t ctx, std::uint64_t value);
std::uint64_t iqjs_dup_value_rt(std::uint64_t rt, std::uint64_t value);
std::int32_t iqjs_get_value_tag(std::uint64_t value);
bool iqjs_is_nan(std::uint64_t value);
bool iqjs_is_number(std::uint64_t value);
bool iqjs_is_bigint(std::uint64_t value);
bool iqjs_is_bool(std::uint64_t value);
bool iqjs_is_null(std::uint64_t value);
bool iqjs_is_undefined(std::uint64_t value);
bool iqjs_is_exception(std::uint64_t value);
bool iqjs_is_uninitialized(std::uint64_t value);
bool iqjs_is_string(std::uint64_t value);
bool iqjs_is_symbol(std::uint64_t value);
bool iqjs_is_object(std::uint64_t value);
bool iqjs_is_module(std::uint64_t value);
bool iqjs_is_error(std::uint64_t value);
bool iqjs_is_uncatchable_error(std::uint64_t value);
void iqjs_set_uncatchable_error(std::uint64_t ctx, std::uint64_t value);
void iqjs_clear_uncatchable_error(std::uint64_t ctx, std::uint64_t value);
void iqjs_reset_uncatchable_error(std::uint64_t ctx);
std::uint64_t iqjs_throw(std::uint64_t ctx, std::uint64_t value);
std::uint64_t iqjs_get_exception(std::uint64_t ctx);
bool iqjs_has_exception(std::uint64_t ctx);
std::uint64_t iqjs_new_error(std::uint64_t ctx);
std::uint64_t iqjs_new_internal_error(std::uint64_t ctx, std::string_view message);
std::uint64_t iqjs_new_plain_error(std::uint64_t ctx, std::string_view message);
std::uint64_t iqjs_new_range_error(std::uint64_t ctx, std::string_view message);
std::uint64_t iqjs_new_reference_error(std::uint64_t ctx, std::string_view message);
std::uint64_t iqjs_new_syntax_error(std::uint64_t ctx, std::string_view message);
std::uint64_t iqjs_new_type_error(std::uint64_t ctx, std::string_view message);
std::uint64_t iqjs_throw_internal_error(std::uint64_t ctx, std::string_view message);
std::uint64_t iqjs_throw_plain_error(std::uint64_t ctx, std::string_view message);
std::uint64_t iqjs_throw_range_error(std::uint64_t ctx, std::string_view message);
std::uint64_t iqjs_throw_reference_error(std::uint64_t ctx, std::string_view message);
std::uint64_t iqjs_throw_syntax_error(std::uint64_t ctx, std::string_view message);
std::uint64_t iqjs_throw_type_error(std::uint64_t ctx, std::string_view message);
std::uint64_t iqjs_throw_dom_exception(std::uint64_t ctx, std::string_view name, std::string_view message);
std::uint64_t iqjs_throw_out_of_memory(std::uint64_t ctx);
std::int32_t iqjs_is_equal(std::uint64_t ctx, std::uint64_t left, std::uint64_t right);
bool iqjs_is_strict_equal(std::uint64_t ctx, std::uint64_t left, std::uint64_t right);
bool iqjs_is_same_value(std::uint64_t ctx, std::uint64_t left, std::uint64_t right);
bool iqjs_is_same_value_zero(std::uint64_t ctx, std::uint64_t left, std::uint64_t right);
std::int32_t iqjs_to_bool(std::uint64_t ctx, std::uint64_t value);
std::uint64_t iqjs_to_boolean(std::uint64_t ctx, std::uint64_t value);
std::uint64_t iqjs_to_number(std::uint64_t ctx, std::uint64_t value);
gm_structs::IQJSInt32Result iqjs_to_int32(std::uint64_t ctx, std::uint64_t value);
gm_structs::IQJSUInt32Result iqjs_to_uint32(std::uint64_t ctx, std::uint64_t value);
gm_structs::IQJSInt64Result iqjs_to_int64(std::uint64_t ctx, std::uint64_t value);
gm_structs::IQJSUInt64Result iqjs_to_index(std::uint64_t ctx, std::uint64_t value);
gm_structs::IQJSFloatResult iqjs_to_float64(std::uint64_t ctx, std::uint64_t value);
gm_structs::IQJSInt64Result iqjs_to_bigint64(std::uint64_t ctx, std::uint64_t value);
gm_structs::IQJSUInt64Result iqjs_to_biguint64(std::uint64_t ctx, std::uint64_t value);
gm_structs::IQJSInt64Result iqjs_to_int64_ext(std::uint64_t ctx, std::uint64_t value);
std::uint64_t iqjs_to_string(std::uint64_t ctx, std::uint64_t value);
std::uint64_t iqjs_to_property_key(std::uint64_t ctx, std::uint64_t value);
std::string iqjs_to_cstring(std::uint64_t ctx, std::uint64_t value, bool cesu8);
std::vector<std::uint16_t> iqjs_to_utf16(std::uint64_t ctx, std::uint64_t value);
std::uint64_t iqjs_new_object(std::uint64_t ctx);
std::uint64_t iqjs_new_object_proto(std::uint64_t ctx, std::uint64_t proto);
std::uint64_t iqjs_new_object_class(std::uint64_t ctx, std::uint64_t class_id);
std::uint64_t iqjs_new_object_proto_class(std::uint64_t ctx, std::uint64_t proto, std::uint64_t class_id);
std::uint64_t iqjs_new_object_from(std::uint64_t ctx, const std::vector<std::uint64_t>& atoms, const std::vector<std::uint64_t>& values);
std::uint64_t iqjs_new_object_from_str(std::uint64_t ctx, const std::vector<std::string_view>& names, const std::vector<std::uint64_t>& values);
std::uint64_t iqjs_to_object(std::uint64_t ctx, std::uint64_t value);
std::uint64_t iqjs_to_object_string(std::uint64_t ctx, std::uint64_t value);
std::uint64_t iqjs_new_array(std::uint64_t ctx);
std::uint64_t iqjs_new_array_from(std::uint64_t ctx, const std::vector<std::uint64_t>& values);
std::uint64_t iqjs_new_date(std::uint64_t ctx, float epoch_ms);
std::uint64_t iqjs_new_proxy(std::uint64_t ctx, std::uint64_t target, std::uint64_t handler);
std::uint64_t iqjs_get_proxy_target(std::uint64_t ctx, std::uint64_t proxy);
std::uint64_t iqjs_get_proxy_handler(std::uint64_t ctx, std::uint64_t proxy);
bool iqjs_is_function(std::uint64_t ctx, std::uint64_t value);
bool iqjs_is_async_function(std::uint64_t value);
bool iqjs_is_constructor(std::uint64_t ctx, std::uint64_t value);
bool iqjs_set_constructor_bit(std::uint64_t ctx, std::uint64_t value, bool enabled);
bool iqjs_is_regexp(std::uint64_t value);
bool iqjs_is_map(std::uint64_t value);
bool iqjs_is_set(std::uint64_t value);
bool iqjs_is_weak_ref(std::uint64_t value);
bool iqjs_is_weak_set(std::uint64_t value);
bool iqjs_is_weak_map(std::uint64_t value);
bool iqjs_is_data_view(std::uint64_t value);
bool iqjs_is_array(std::uint64_t value);
bool iqjs_is_proxy(std::uint64_t value);
bool iqjs_is_date(std::uint64_t value);
std::uint64_t iqjs_get_property(std::uint64_t ctx, std::uint64_t object, std::uint64_t atom);
std::uint64_t iqjs_get_property_uint32(std::uint64_t ctx, std::uint64_t object, std::uint32_t index);
std::uint64_t iqjs_get_property_int64(std::uint64_t ctx, std::uint64_t object, std::int64_t index);
std::uint64_t iqjs_get_property_str(std::uint64_t ctx, std::uint64_t object, std::string_view name);
std::int32_t iqjs_set_property(std::uint64_t ctx, std::uint64_t object, std::uint64_t atom, std::uint64_t value);
std::int32_t iqjs_set_property_uint32(std::uint64_t ctx, std::uint64_t object, std::uint32_t index, std::uint64_t value);
std::int32_t iqjs_set_property_int64(std::uint64_t ctx, std::uint64_t object, std::int64_t index, std::uint64_t value);
std::int32_t iqjs_set_property_str(std::uint64_t ctx, std::uint64_t object, std::string_view name, std::uint64_t value);
std::int32_t iqjs_has_property(std::uint64_t ctx, std::uint64_t object, std::uint64_t atom);
std::int32_t iqjs_is_extensible(std::uint64_t ctx, std::uint64_t object);
std::int32_t iqjs_prevent_extensions(std::uint64_t ctx, std::uint64_t object);
std::int32_t iqjs_delete_property(std::uint64_t ctx, std::uint64_t object, std::uint64_t atom, gm_enums::IQJSPropertyFlags flags);
std::int32_t iqjs_set_prototype(std::uint64_t ctx, std::uint64_t object, std::uint64_t proto);
std::uint64_t iqjs_get_prototype(std::uint64_t ctx, std::uint64_t object);
gm_structs::IQJSInt64Result iqjs_get_length(std::uint64_t ctx, std::uint64_t object);
std::int32_t iqjs_set_length(std::uint64_t ctx, std::uint64_t object, std::int64_t new_length);
std::int32_t iqjs_seal_object(std::uint64_t ctx, std::uint64_t object);
std::int32_t iqjs_freeze_object(std::uint64_t ctx, std::uint64_t object);
std::vector<gm_structs::IQJSPropertyEnumEntry> iqjs_get_own_property_names(std::uint64_t ctx, std::uint64_t object, gm_enums::IQJSGPNFlags flags);
gm_structs::IQJSPropertyDescriptorResult iqjs_get_own_property(std::uint64_t ctx, std::uint64_t object, std::uint64_t atom);
std::int32_t iqjs_define_property(std::uint64_t ctx, std::uint64_t object, std::uint64_t atom, std::uint64_t value, std::uint64_t getter, std::uint64_t setter, gm_enums::IQJSPropertyFlags flags);
std::int32_t iqjs_define_property_value(std::uint64_t ctx, std::uint64_t object, std::uint64_t atom, std::uint64_t value, gm_enums::IQJSPropertyFlags flags);
std::int32_t iqjs_define_property_value_uint32(std::uint64_t ctx, std::uint64_t object, std::uint32_t index, std::uint64_t value, gm_enums::IQJSPropertyFlags flags);
std::int32_t iqjs_define_property_value_str(std::uint64_t ctx, std::uint64_t object, std::string_view name, std::uint64_t value, gm_enums::IQJSPropertyFlags flags);
std::int32_t iqjs_define_property_get_set(std::uint64_t ctx, std::uint64_t object, std::uint64_t atom, std::uint64_t getter, std::uint64_t setter, gm_enums::IQJSPropertyFlags flags);
std::int32_t iqjs_set_constructor(std::uint64_t ctx, std::uint64_t function_value, std::uint64_t proto);
std::int32_t iqjs_is_instance_of(std::uint64_t ctx, std::uint64_t value, std::uint64_t object);
void iqjs_set_is_html_dda(std::uint64_t ctx, std::uint64_t object);
std::int32_t iqjs_unsafe_set_opaque(std::uint64_t object, std::uint64_t pointer);
std::uint64_t iqjs_unsafe_get_opaque(std::uint64_t object, std::uint64_t class_id);
std::uint64_t iqjs_unsafe_get_opaque2(std::uint64_t ctx, std::uint64_t object, std::uint64_t class_id);
gm_structs::IQJSOpaqueResult iqjs_unsafe_get_any_opaque(std::uint64_t object);
bool iqjs_detect_module(std::string_view source);
std::uint64_t iqjs_eval(std::uint64_t ctx, std::string_view source, std::string_view filename, gm_enums::IQJSEvalFlags flags);
std::uint64_t iqjs_eval2(std::uint64_t ctx, std::string_view source, const gm_structs::IQJSEvalOptions& options);
std::uint64_t iqjs_eval_this(std::uint64_t ctx, std::uint64_t this_value, std::string_view source, std::string_view filename, gm_enums::IQJSEvalFlags flags);
std::uint64_t iqjs_eval_this2(std::uint64_t ctx, std::uint64_t this_value, std::string_view source, const gm_structs::IQJSEvalOptions& options);
std::uint64_t iqjs_eval_function(std::uint64_t ctx, std::uint64_t function_value);
std::uint64_t iqjs_get_global_object(std::uint64_t ctx);
std::uint64_t iqjs_parse_json(std::uint64_t ctx, std::string_view json, std::string_view filename);
std::uint64_t iqjs_json_stringify(std::uint64_t ctx, std::uint64_t object, std::uint64_t replacer, std::uint64_t space);
std::uint64_t iqjs_new_array_buffer_copy(std::uint64_t ctx, gm::wire::GMBuffer data);
std::uint64_t iqjs_new_array_buffer_owned(std::uint64_t ctx, gm::wire::GMBuffer data, bool is_shared);
void iqjs_detach_array_buffer(std::uint64_t ctx, std::uint64_t object);
std::int64_t iqjs_copy_array_buffer(std::uint64_t ctx, std::uint64_t object, gm::wire::GMBuffer destination);
std::vector<std::uint8_t> iqjs_get_array_buffer_copy(std::uint64_t ctx, std::uint64_t object);
bool iqjs_is_array_buffer(std::uint64_t object);
std::int32_t iqjs_is_immutable_array_buffer(std::uint64_t object);
std::int32_t iqjs_set_immutable_array_buffer(std::uint64_t object, bool immutable);
std::vector<std::uint8_t> iqjs_get_uint8_array_copy(std::uint64_t ctx, std::uint64_t object);
std::uint64_t iqjs_new_typed_array(std::uint64_t ctx, const std::vector<std::uint64_t>& arguments, gm_enums::IQJSTypedArrayType array_type);
gm_structs::IQJSTypedArrayBufferInfo iqjs_get_typed_array_buffer(std::uint64_t ctx, std::uint64_t object);
std::uint64_t iqjs_new_uint8_array_copy(std::uint64_t ctx, gm::wire::GMBuffer data);
std::uint64_t iqjs_new_uint8_array_owned(std::uint64_t ctx, gm::wire::GMBuffer data, bool is_shared);
std::int32_t iqjs_get_typed_array_type(std::uint64_t object);
void iqjs_unsafe_set_shared_array_buffer_policy(std::uint64_t rt, std::string_view policy, std::uint64_t opaque);
gm_structs::IQJSPromiseCapability iqjs_new_promise_capability(std::uint64_t ctx);
gm_enums::IQJSPromiseState iqjs_promise_state(std::uint64_t ctx, std::uint64_t promise);
std::uint64_t iqjs_promise_result(std::uint64_t ctx, std::uint64_t promise);
bool iqjs_is_promise(std::uint64_t value);
std::uint64_t iqjs_new_settled_promise(std::uint64_t ctx, bool is_reject, std::uint64_t value);
std::uint64_t iqjs_module_registry_create(std::uint64_t rt);
void iqjs_module_registry_add(std::uint64_t registry, std::string_view name, std::string_view source);
void iqjs_module_registry_remove(std::uint64_t registry, std::string_view name);
void iqjs_module_registry_set_supported_attributes(std::uint64_t registry, const std::vector<std::string_view>& attributes);
void iqjs_module_registry_install(std::uint64_t rt, std::uint64_t registry, bool attributes_aware);
void iqjs_module_registry_free(std::uint64_t registry);
std::uint64_t iqjs_get_import_meta(std::uint64_t ctx, std::uint64_t module_handle);
std::uint64_t iqjs_get_module_name(std::uint64_t ctx, std::uint64_t module_handle);
std::uint64_t iqjs_get_module_namespace(std::uint64_t ctx, std::uint64_t module_handle);
std::int32_t iqjs_set_module_private_value(std::uint64_t ctx, std::uint64_t module_handle, std::uint64_t value);
std::uint64_t iqjs_get_module_private_value(std::uint64_t ctx, std::uint64_t module_handle);
std::uint64_t iqjs_load_module(std::uint64_t ctx, std::string_view basename, std::string_view filename);
std::int32_t iqjs_resolve_module(std::uint64_t ctx, std::uint64_t object);
std::uint64_t iqjs_get_script_or_module_name(std::uint64_t ctx, std::int32_t levels);
std::uint64_t iqjs_new_c_module_adapter(std::uint64_t ctx, std::string_view name, const std::vector<std::string_view>& export_names);
std::int32_t iqjs_add_module_export(std::uint64_t ctx, std::uint64_t module_handle, std::string_view name);
std::int32_t iqjs_set_module_export(std::uint64_t ctx, std::uint64_t module_handle, std::string_view name, std::uint64_t value);
std::int32_t iqjs_set_property_function_list_adapter(std::uint64_t ctx, std::uint64_t object, const std::vector<gm_structs::IQJSFunctionListEntry>& entries);
std::int32_t iqjs_add_module_export_list_adapter(std::uint64_t ctx, std::uint64_t module_handle, const std::vector<gm_structs::IQJSFunctionListEntry>& entries);
std::int32_t iqjs_set_module_export_list_adapter(std::uint64_t ctx, std::uint64_t module_handle, const std::vector<gm_structs::IQJSFunctionListEntry>& entries);
std::vector<std::uint8_t> iqjs_write_object(std::uint64_t ctx, std::uint64_t object, gm_enums::IQJSWriteObjectFlags flags);
gm_structs::IQJSSerializedObject iqjs_unsafe_write_object2(std::uint64_t ctx, std::uint64_t object, gm_enums::IQJSWriteObjectFlags flags);
std::uint64_t iqjs_read_object(std::uint64_t ctx, gm::wire::GMBuffer data, gm_enums::IQJSReadObjectFlags flags);
std::uint64_t iqjs_unsafe_read_object2(std::uint64_t ctx, gm::wire::GMBuffer data, gm_enums::IQJSReadObjectFlags flags, const std::vector<std::uint64_t>& shared_array_buffer_pointers);
std::uint64_t iqjs_set_interrupt_handler_adapter(std::uint64_t rt, const gm::wire::GMFunction& callback);
std::uint64_t iqjs_set_host_promise_rejection_tracker_adapter(std::uint64_t rt, const gm::wire::GMFunction& callback);
std::uint64_t iqjs_set_promise_hook_adapter(std::uint64_t rt, const gm::wire::GMFunction& callback);
void iqjs_remove_callback_adapter(std::uint64_t registration);
std::uint64_t iqjs_new_gml_function_adapter(std::uint64_t ctx, std::string_view name, std::int32_t function_length, std::int32_t magic, const gm::wire::GMFunction& callback);
std::uint64_t iqjs_new_gml_function_data_adapter(std::uint64_t ctx, std::string_view name, std::int32_t function_length, std::int32_t magic, const std::vector<std::uint64_t>& data, const gm::wire::GMFunction& callback);
std::uint64_t iqjs_new_gml_closure_adapter(std::uint64_t ctx, std::string_view name, std::int32_t function_length, std::int32_t magic, const gm::wire::GMFunction& callback, const gm::wire::GMFunction& finalize_callback);
std::int32_t iqjs_register_gml_global_function(std::uint64_t ctx, std::string_view name, const gm::wire::GMFunction& callback);
void iqjs_unregister_gml_global_function(std::uint64_t ctx, std::string_view name);
std::int32_t iqjs_enqueue_job_adapter(std::uint64_t ctx, std::uint64_t function_value, const std::vector<std::uint64_t>& arguments);
std::uint64_t iqjs_call(std::uint64_t ctx, std::uint64_t function_value, std::uint64_t this_value, const std::vector<std::uint64_t>& arguments);
std::uint64_t iqjs_invoke(std::uint64_t ctx, std::uint64_t this_value, std::uint64_t atom, const std::vector<std::uint64_t>& arguments);
std::uint64_t iqjs_call_constructor(std::uint64_t ctx, std::uint64_t function_value, const std::vector<std::uint64_t>& arguments);
std::uint64_t iqjs_call_constructor2(std::uint64_t ctx, std::uint64_t function_value, std::uint64_t new_target, const std::vector<std::uint64_t>& arguments);
