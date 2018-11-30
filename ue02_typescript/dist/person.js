"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
class Person {
    constructor(vorname, nachname, birthYear) {
        this._vorname = vorname;
        this._nachname = nachname;
        this._birthYear = birthYear;
    }
    get vorname() {
        return this._vorname;
    }
    get nachname() {
        return this._nachname;
    }
    get birthYear() {
        return this._birthYear;
    }
    set vorname(v) {
        if (v === undefined || v === null || v === '') {
            throw Error('invalid value');
        }
        this._vorname = v;
    }
    toString() {
        return this._nachname + ' ' + this._vorname;
    }
}
exports.Person = Person;

//# sourceMappingURL=person.js.map
