"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const server_1 = require("./server");
class Main {
    static main() {
        const server = new server_1.Server(4711);
        server.start();
    }
}
Main.main();

//# sourceMappingURL=main.js.map
