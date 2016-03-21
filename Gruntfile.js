var copySrcDir = "node_modules/";
var copyDestDir = "src/main/resources/public/";

module.exports = function(grunt) {
    grunt.loadNpmTasks("grunt-ts");
    grunt.loadNpmTasks("grunt-contrib-copy");
    grunt.initConfig({
        pkg: grunt.file.readJSON("package.json"),
        ts: {
            app: {
                src: [
                      'node_modules/angular2/typings/browser.d.ts',
                      'src/main/ts/**/*.ts'
                      ],
                dest: 'src/main/resources/public/app/',
                options: {
                    module: 'system', 
                    moduleResolution: 'node',
                    target: 'es5',
                    experimentalDecorators: true,
                    emitDecoratorMetadata: true,
                    noImplicitAny: false
                }
            }
        },
        copy: {
        	main: {
        		// Copy angular's templates 
	        	files: [{
	                expand: true, 
	                cwd: 'src/main/ts/',
	                src: '**/*.html',
	                dest: 'src/main/resources/public/app/'
	            },
	            // Copy vendor javascript files
	            {
	            	expand: true, 
	            	src: copySrcDir + 'es6-shim/es6-shim.min.js',
	            	dest: copyDestDir
	            },
	            {
	            	expand: true, 
	            	src: copySrcDir + 'systemjs/dist/system-polyfills.js',
	            	dest: copyDestDir
	            },
	            {
	            	expand: true, 
	            	src: copySrcDir + 'angular2/es6/dev/src/testing/shims_for_IE.js',
	            	dest: copyDestDir
	            },
	            {
	            	expand: true, 
	            	src: copySrcDir + 'angular2/bundles/angular2-polyfills.js',
	            	dest: copyDestDir
	            },
	            {
	            	expand: true, 
	            	src: copySrcDir + 'systemjs/dist/system.src.js',
	            	dest: copyDestDir
	            },
	            {
	            	expand: true, 
	            	src: copySrcDir + 'rxjs/bundles/Rx.js',
	            	dest: copyDestDir
	            },
	            {
	            	expand: true, 
	            	src: copySrcDir + 'angular2/bundles/angular2.dev.js',
	            	dest: copyDestDir
	            },
	            {
	            	expand: true, 
	            	src: copySrcDir + 'angular2/bundles/router.dev.js',
	            	dest: copyDestDir
	            }]
        	}
        }
        	
    });
    
    grunt.registerTask("compile", ["ts", "copy"]);

    grunt.registerTask("test", []);
}
