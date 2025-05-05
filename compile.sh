BINARY="./build/bin/Escape-To-Eclipse";

cmake --build ./build;
if [ -x "$BINARY" ]; then
	$BINARY;
else
	chmod 777 "$BINARY";
	$BINARY;
fi

echo "Executing $BINARY"

