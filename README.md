<h1>Compass, searchs algorithms library </h1>
Compass is an open library witch offers some search algorithms easy to use. For the moment there is only an implementation of A* algorithm but I will maybe add some others in the futur. If you want to contribute do not hesitate to ask.

<h2>Configuration</h2>

Just add the folder "Compass/include" in your project and the header "Compass.hpp".<br>
<code> #include "...Compass/include/Compass.hpp" </code>

<h2>ASTAR | How to find my way in a 2D Map</h2>

There is a recurent problematic for games. Pathfinding is very usefull when you want to find the path from a point A to a point B. AStar is a good algorithm for this sort of problems and there is an implementation.</br>
<code>

    // Load map from file 
    Compass::PCore::Matrix<int> mapi = getMapFromFile("mapInput.txt");
    
    // Config parameters for the algorithm 
    Compass::PPathfinding::AStar  astar;
    astar.smoothPath(true); //To have smoot path
    astar.init(&mapi);

    // Find the path from pend to pstart
    Compass::PCore::Point pend(2,2);
    Compass::PCore::Point pstart(8,8);
    std::list<Compass::PCore::Point> res = astar.run(pend,pstart);

    // Save result in file 
    savePathInFile("outFile.txt",mapi,res);
</code>



