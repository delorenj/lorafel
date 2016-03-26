var gulp = require('gulp');
var glue = require("gulp-glue");
var rename = require("gulp-rename");

gulp.task('sprites:pack', function() {
    return gulp
        .src(['/Users/delorenj/cc/Lorafel/sprites/raw/**/*.*'])
        .pipe(glue({
            'source': '/Users/delorenj/cc/Lorafel/sprites/raw',
            'output': '/Users/delorenj/cc/Lorafel/sprites/sheets',                      // required
            'project': true,
            'retina': false,
            'cocos2d': true
        }))
    ;
});

gulp.task('sprites:copy', function() {
   return gulp
       .src('/Users/delorenj/cc/Lorafel/sprites/sheets/*')
       .pipe(rename(function(path){
           var name = path.basename;
           path.dirname = name;
           path.basename = "sprites";
       }))
       .pipe(gulp.dest("/Users/delorenj/code/Lorafel/Resources"))
    ;
});

gulp.task('default', ['sprites:pack', 'sprites:copy']);