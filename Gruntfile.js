module.exports = function(grunt) {
    grunt.loadNpmTasks("grunt-ts");
    grunt.initConfig({
        pkg: grunt.file.readJSON("package.json"),
        ts: {
            app: {
                src: [
                      'node_modules/angular2/typings/browser.d.ts',
                      'app/**/*.ts'
                      ],
                dest: 'app',
                options: {
                    module: 'system', 
                    moduleResolution: 'node',
                    target: 'es5',
                    experimentalDecorators: true,
                    emitDecoratorMetadata: true,
                    noImplicitAny: false
                }
            }
        }
    });
    
    grunt.registerTask("compile", ["ts"]);
}
