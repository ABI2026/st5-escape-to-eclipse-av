# Escape To Eclipse :alien:
## :information_source: Concept Description:

This game is primary about the colonialisation of new scapes in further space, we don't know already. You and your SpaceShip are on an exploration mission. Some planets are friendly and some planets are hostile. While playing you have to get new ressources for further exploration from uknown planets. You can trade or you have to fight. 

## :hammer: Compiler Configuration with CMake

Instructions to compile the Game

<table>
    <tr>
        <td>Create build folder with:</td>
        <td><code>mkdir -p build && cd ./build</code></td>
    </tr>
    <tr>
        <td>Configure Build:</td>
        <td><code>cmake -DCMAKE_BUILD_TYPE=DEBUG ..</code></td>
    </tr>
    <tr>
        <td>Build the program:</td>
        <td><code>sudo make -j$(nproc)</code></td>
    </tr>
    <tr>
        <td>Execute the Game:</td>
        <td><code>$USER/SOURCEDIR/build: ./bin/Escape-To-Eclipse</code></td>
    </tr>
    <tr>
        <td>(If needed, refresh permissions)</td>
        <td><code>sudo chmod 777 ./bin/Escape-To-Eclipse</code></td>
    </tr>
</table>
