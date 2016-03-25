var gulp = require('gulp');
var glue = require("gulp-sprite-glue");

var iphonehd5 = function() {
    gulp.src("./joeman/*")
        .pipe(
            glue("./Resources/iphonehd5/*.png",{
                cocos2d: true
            })
        )
    ;
};

gulp.task('sprites:iphonehd5', function() {
    return iphonehd5();
});

gulp.task('default', ['sprites:iphonehd5']);