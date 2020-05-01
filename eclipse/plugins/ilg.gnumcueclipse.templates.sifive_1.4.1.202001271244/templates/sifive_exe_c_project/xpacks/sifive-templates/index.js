/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2017 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

'use strict'

/**
 * This is the module entry point, the file that is processed when
 * `require('<module>')` is called.
 *
 * For this to work, it must be linked from `package.json` as
 * `"main": "./index.js",`, which is, BTW, the default behaviour.
 *
 * To import classes from this module into Node.js applications, use:
 *
 * ```javascript
 * const Main = require('<module>').Main
 * const XpmInitTemplate = require('<module>').XpmInitTemplate
 * ```
 */

// ES6: `import { Main } from './lib/main.js'
const Main = require('./lib/main.js').Main
// ES6: `import { XpmInitTemplate } from './lib/template.js'
const XpmInitTemplate = require('./lib/template.js').XpmInitTemplate

// ----------------------------------------------------------------------------
// Node.js specific export definitions.

// By default, `module.exports = {}`.
// The Main class is added as a property with the same name to this object.

module.exports.Main = Main
module.exports.XpmInitTemplate = XpmInitTemplate

// In ES6, it would be:
// export class Main { ... }
// export class XpmInitTemplate { ... }
// ...
// import { Main } from 'module.js'
// import { XpmInitTemplate } from 'module.js'

// ----------------------------------------------------------------------------
