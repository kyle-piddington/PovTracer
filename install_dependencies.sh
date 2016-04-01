#/bin/bash
#Download the latest versions of GLEW, GLFW, and SOIL
CDIR=$(pwd)
if [ ! -d include ] ; then
   mkdir include
fi

if [ ! -d thirdparty ] ; then
   mkdir thirdparty
fi

if [ ! -d thirdparty/catch ] ; then
   git clone https://github.com/philsquared/Catch.git thirdparty/Catch
   mkdir include/catch
   ln -s $CDIR/thirdparty/Catch/single_include/catch.hpp include/catch/catch.hpp
fi

if [ ! -d thridparty/stb ] ; then
   mkdir thirdparty/stb
   curl https://raw.githubusercontent.com/nothings/stb/master/stb_image.h -o thirdparty/stb/stb_image.h
   curl https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h -o thirdparty/stb/stb_image_write.h
   ln -s $CDIR/thirdparty/stb include/stb
fi
