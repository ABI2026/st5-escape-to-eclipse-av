BUILD_DIR="./build"

if [ -d "$BUILD_DIR" ]; then
	cmake --build $BUILD_DIR;
else
	mkdir -p build;
	cmake -S ./ -B $BUILD_DIR;
	cmake --build $BUILD_DIR;
fi

BINARY="$BUILD_DIR/bin/Escape-To-Eclipse";

if [ -x "$BINARY" ]; then
	$BINARY;
else
	chmod 777 "$BINARY";
	$BINARY;
fi

echo "Executing $BINARY"

