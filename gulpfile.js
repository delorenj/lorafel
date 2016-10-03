var gulp = require('gulp');
var shell = require('gulp-shell');
var copy = require("gulp-copy");
var rename = require("gulp-rename");

gulp.task('sprites:pack', function () {
    return gulp.src(['/Users/delorenj/cc/Lorafel/sprites/raw/*'], {read: false})
        .pipe(shell([
            'echo Packing sprites in <%= f(file.path) %>...',
            'mkdir -p <%= file.path %>/../../sheets/<%= f(file.path) %>',
            'TexturePacker --data <%= file.path %>/../../sheets/<%= f(file.path) %>/sprites.plist --format cocos2d --sheet <%= file.path %>/../../sheets/<%= f(file.path) %>/sprites.png <%= file.path %>'
            // 'spriteglue <%= file.path %> --sheet <%= file.path %>/../../sheets/<%= f(file.path) %>/sprites.png --margin=0 --padding=0 --max-size-w=2048 --max-size-h=2048 --trim=none',
        ], {
            templateData: {
                f: function(s) {
                    var splits = s.split('/');
                    return splits[splits.length-1];
                }
            }
        }))
})

gulp.task('sprites:copy',['sprites:pack'], function() {
   return gulp
       .src([
           '/Users/delorenj/cc/Lorafel/sprites/sheets/**/sprites.*',
           '/Users/delorenj/cc/Lorafel/sprites/nss/**/*'
       ])
       .pipe(gulp.dest("/Users/delorenj/code/Lorafel/Resources"))

    ;
});

gulp.task('particles:copy', function() {
    return gulp
        .src('/Users/delorenj/cc/Lorafel/particles/plists/*')
        .pipe(gulp.dest("/Users/delorenj/code/Lorafel/Resources/iphonehd5"))
        .pipe(gulp.dest("/Users/delorenj/code/Lorafel/Resources/iphonehd"))
        .pipe(gulp.dest("/Users/delorenj/code/Lorafel/Resources/iphone"))
        .pipe(gulp.dest("/Users/delorenj/code/Lorafel/Resources/ipadhd"))
        .pipe(gulp.dest("/Users/delorenj/code/Lorafel/Resources/ipad"))
        .pipe(gulp.dest("/Users/delorenj/code/Lorafel/Resources/ultra4k"))
        ;

});

gulp.task('default', ['sprites:pack', 'sprites:copy', 'particles:copy']);