# Escape To Eclipse :alien:
### :information_source: Concept Description:

This game is primary about the colonialisation of new scapes in further space, we don't know already. You and your SpaceShip are on an exploration mission. Some planets are friendly and some planets are hostile. While playing you have to get new ressources for further exploration from uknown planets. You can trade or you have to fight. 

### :hammer: Compiler Configuration with CMake

Instructions to compile the Game

<ol>
    <li> Create build folder with: <code>mkdir -p build</code><li>
    <li> Configure build: <code>cmake -DCMAKE_BUILD_TYPE=DEBUG ..</code><li>
    <li> Build the Game: <code>make -j$(nproc)</code><li>
    <li> Execute the program: <code>./build/bin/Escape-To-Eclipse</code><li>
    <li> (Set permissions if needed): <code>chmod 777 ./build/bin/Escape-To-Eclipse</code><li>
</ol>

