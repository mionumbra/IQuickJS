const argv = process.argv.slice(2);
const fs = require("fs");

if (argv.length < 2) {
    console.log("Usage: <input> <output>");
    process.exit(1);
}

const milmth_chart = fs.readFileSync(argv[0], "utf-8");
const ENV = {
    "stage.width": 1920,
    "stage.height": 1080,
};

function lerpTime(f, t, p) {
    if (Array.isArray(f) && Array.isArray(t)) {
        if (f.length != t.length) {
            throw new Error("Both arrays must have the same length");
        }

        if (f.length == 4) {
            if (f[3] != t[3]) {
                throw new Error("Both arrays must have the same 4th element");
            }
        }

        const fr = f[0] + f[1] / f[2];
        const tr = t[0] + t[1] / t[2];

        return f.length == 3 ? [ fr + (tr - fr) * p, 0, 1 ] : [ fr + (tr - fr) * p, 0, 1, f[3] ];
    } else if (!Array.isArray(f) && !Array.isArray(t)) {
        return f + (t - f) * p;
    } else {
        throw new Error("Both arguments must be arrays");
    }
}

function customExpValue(expr, t) {
    with (Math) {
        const mod = (x, y) => x % y;
        return eval(expr);
    }
}

class MilizeBeatmapClass {
    constructor() {
        this.mil = {
            meta: {},
            bpms: [],
            lines: [],
            storyboardObjects: [],
            animations: []
        };
        this._note_index = 0;
    }

    /**
     * BeatmapAddBpm (float start, float bpm, int beatsPerBar)
     * @param {Number} start 
     * @param {Number} bpm 
     * @param {Number} beatsPerBar 
     */
    timing(start, bpm, beatsPerBar) {
        beatmap.mil.bpms.push({
            start: start,
            bpm: bpm,
            beatsPerBar: beatsPerBar
        });

        return beatmap.mil.bpms.length - 1;
    }

    /**
     * BeatmapAddStoryboardObject (int type, IntPtr data, int layer)
     * @param {Number} type 
     * @param {Number} data 
     * @param {Number} layer 
     */
    storyboardObject(type, data, layer) {
        beatmap.mil.storyboardObjects.push({
            type: type,
            data: data,
            layer: layer
        });

        return beatmap.mil.storyboardObjects.length - 1;
    }

    /**
     * BeatmapAddNote (int line, int bpm, IntPtr startTime, IntPtr endTime, int type, int isFake, int isAlwaysPerfect)
     * @param {Number} line 
     * @param {Number} bpm 
     * @param {Number} startTime 
     * @param {Number} endTime 
     * @param {Number} type 
     * @param {Boolean} isFake 
     * @param {Boolean} isAlwaysPerfect 
     */
    note(line, bpm, startTime, endTime, type, isFake, isAlwaysPerfect) {
        // if (type == 1 && isAlwaysPerfect) {
        //     // throw new Error("WTF");
        //     isAlwaysPerfect = false;
        // }

        beatmap.mil.lines[line].notes.push({
            bpm: bpm,
            startTime: startTime,
            endTime: endTime,
            type: type,
            isFake: isFake,
            isAlwaysPerfect: isAlwaysPerfect,
            index: beatmap._note_index++
        });

        return beatmap.mil.lines[line].notes[beatmap.mil.lines[line].notes.length - 1].index;
    }

    /**
     * BeatmapAddAnimation (int bpmId, IntPtr fromBeat, IntPtr toBeat, int key, IntPtr fv, IntPtr tv, int data, int i1, int press, int ease, int valueExpression, IntPtr customEaseExpression)
     * @param {Number} bpmId 
     * @param {Number} fromBeat 
     * @param {Number} toBeat 
     * @param {Number} key 
     * @param {String} fv 
     * @param {String} tv 
     * @param {Number} data 
     * @param {Number} i1 
     * @param {Number} press 
     * @param {Number} ease 
     * @param {Boolean} valueExpression 
     * @param {String} customEaseExpression 
     */
    animation(bpmId, fromBeat, toBeat, key, fv, tv, data, i1, press, ease, valueExpression, customEaseExpression) {
        const event = {
            bpmId: bpmId,
            fromBeat: fromBeat,
            toBeat: toBeat,
            key: key,
            fv: fv,
            tv: tv,
            data: data,
            i1: i1,
            press: press,
            ease: ease,
            valueExpression: valueExpression,
            customEaseExpression: customEaseExpression,
            // magicFlag: valueExpression,
            // magicArr: []
        };
        beatmap.mil.animations.push(event);

        // if (!valueExpression) {
        //     beatmap.mil.animations.push(event);
        //     return;
        // }

        // const k = 16384;

        // for (let i = 0; i <= k; i++) {
        //     let p = i / k;
        //     let v = customExpValue(customEaseExpression, p);
        //     event.magicArr.push(v);
        // }

        // beatmap.mil.animations.push(event);
    }

    withProperty(key, value) {
        beatmap.mil.meta[key] = value;
        return beatmap;
    }

    line() {
        beatmap.mil.lines.push({
            notes: []
        });

        return beatmap.mil.lines.length - 1;
    }

    env(key) {
        return ENV[key];
    }

    _convertTime(time, bpm) {
        if (!Array.isArray(time)) return time;
        if (time.length !== 3 && time.length !== 4) return 0;

        const beatTime = (time[0] + time[1] / time[2]);
        const bpmObject = beatmap.mil.bpms[time.length === 3 ? bpm : time[3]]; // || {
        //     bpm: bpm,
        //     start: 0
        // };

        return bpmObject.start + beatTime * (60 / bpmObject.bpm);
    }

    _afterLoad() {
        for (const line of beatmap.mil.lines) {
            for (const note of line.notes) {
                note.startTime = this._convertTime(note.startTime, note.bpm);
                note.endTime = this._convertTime(note.endTime, note.bpm);
                note.bpm = 0;
            }
        }

        for (const anim of beatmap.mil.animations) {
            anim.fromBeat = this._convertTime(anim.fromBeat, anim.bpmId);
            anim.toBeat = this._convertTime(anim.toBeat, anim.bpmId);
            anim.bpmId = 0;
        }
    }
}

const beatmap = new MilizeBeatmapClass();
const MilizeBeatmap = beatmap;
eval(milmth_chart);
// MilizeBeatmap._afterLoad();

fs.writeFileSync(argv[1], JSON.stringify(beatmap.mil));
