#include <pch.h>
#include "Projects/ProjectTwo.h"
#include "P2_Pathfinding.h"

#pragma region Extra Credit
bool ProjectTwo::implemented_floyd_warshall()
{
    return false;
}

bool ProjectTwo::implemented_goal_bounding()
{
    return false;
}

bool ProjectTwo::implemented_jps_plus()
{
    return false;
}
#pragma endregion
AStarPather::AStarPather() :mapWidth{ 40 }, mapHeight{ 40 } {
    
    MapPath = new Node * [terrain->maxMapHeight];
    for (int i = 0; i < terrain->maxMapHeight; i++) {
        MapPath[i] = new Node[terrain->maxMapWidth];
    }

}
void AStarPather::initializeMapSize(void) {
    mapWidth = terrain->get_map_width();
    mapHeight = terrain->get_map_height();
    for (int i = 0; i < mapHeight; i++) {

        for (int j = 0; j < mapWidth; j++) {
            MapPath[i][j].fx = 0;
            MapPath[i][j].gx = 0;
            MapPath[i][j].hx = 0;
            MapPath[i][j].gridpos.col = j;
            MapPath[i][j].gridpos.row = i;
            MapPath[i][j].parent = nullptr;
            MapPath[i][j].list = empty;


        }

    }
    NopenL.clear();
}



bool AStarPather::initialize()
{
    // handle any one-time setup requirements you have
    Callback cb = std::bind(&AStarPather::initializeMapSize, this);
    Messenger::listen_for_message(Messages::MAP_CHANGE, cb);
    
    /*
        If you want to do any map-preprocessing, you'll need to listen
        for the map change message.  It'll look something like this:
        There are other alternatives to using std::bind, so feel free to mix it up.
        Callback is just a typedef for std::function<void(void)>, so any std::invoke'able
        object that std::function can wrap will suffice.
    */

    return true; // return false if any errors actually occur, to stop engine initialization
}

void AStarPather::shutdown()
{
    /*
        Free any dynamically allocated memory or any other general house-
        keeping you need to do during shutdown.
    */
}

float AStarPather::CalcHeuristics(PathRequest::Settings heuristic, GridPos PositionToUse,GridPos start) {
    float distance=0; 
    switch (heuristic.heuristic) {
    case Heuristic::OCTILE:

        //GridPos pospos = terrain->get_grid_position((Vec3)*request.path.end());
        //check 8 corners 
        /*
        when C pop open 8 corner
        TL    T    TR
           \  |  /
            \ | /
        L---- C ----R
            / | \
           /  |  \
        BL    B    BR

        TL == C.c - 1, C.r + 1
        T  == C.c 0  , C.r + 1
        TR == C.c + 1, C.r + 1
        L  == C.c - 1, C.r 0
        ----------------------
        R  == C.c + 1, C.r 0
        BL == C.c - 1, C.r - 1
        B  == C.c 0  , C.r - 1
        BR == C.c + 1, C.r - 1


        */

        distance = (float)(std::min(PositionToUse.col, PositionToUse.row) * sqrtf(2.f)) +
            (float)std::max(PositionToUse.col, PositionToUse.row) - (float)std::min(PositionToUse.col, PositionToUse.row);
        break;

    case Heuristic::CHEBYSHEV:

        distance = (float)std::max(PositionToUse.row, PositionToUse.col);

        break;

    case Heuristic::INCONSISTENT:

        if ((PositionToUse.row + PositionToUse.col) % 2 > 0) {

            distance = sqrtf((float)(PositionToUse.col * PositionToUse.col) + (float)(PositionToUse.row * PositionToUse.row));

        }

        break;

    case Heuristic::MANHATTAN:

        distance = (float)PositionToUse.row + (float)PositionToUse.col;

        break;

    case Heuristic::EUCLIDEAN:

        //x^2 + y^2
        distance = sqrtf((float)(PositionToUse.col * PositionToUse.col) + (float)(PositionToUse.row * PositionToUse.row));
        break;
    }
    return distance;
}


bool isDest(int row , int col , GridPos Dest) {

    return (row == Dest.row && col == Dest.col);
}

std::vector<GridPos> AStarPather::rubberBanding(std::vector <GridPos> arrayy) {
    
    if (arrayy.size()<3) {
        return arrayy;
    }
    
    for (size_t i = 0; i <= arrayy.size()-3;) {
        if (arrayy.size()<=2) {
            break;
        }
        int minx, miny, maxx, maxy;
        
        minx = std::min(arrayy[i].col, arrayy[i + 2].col);
        miny = std::min(arrayy[i].row, arrayy[i + 2].row);

        maxx = std::max(arrayy[i].col, arrayy[i + 2].col);
        maxy = std::max(arrayy[i].row, arrayy[i + 2].row);
        bool deleted = true;
        for (int row = miny; row <= maxy; row++) {
            for (int col = minx; col <= maxx; col++) {
                if (terrain->is_wall(row,col)) {
                    
                    deleted = false;
                    break;

                }
            }
            if (!deleted) {
                break;
            }
        }
        if (!deleted) {
            i++;
        }
        else {
            arrayy.erase(arrayy.begin() + i + 1);
        }
        
    }
    return arrayy;

}



std::vector<Vec3> AStarPather::CalcCMRS(std::vector<GridPos> PathOld) {
    std::vector<Vec3> newPath, Path;
    std::reverse(PathOld.begin(), PathOld.end());
    //iterate through whole path of grids
    for (size_t i = 0; i < PathOld.size(); i++) {
        Path.push_back(terrain->get_world_position(PathOld[i]));

    }
    float Distance = Vec3::Distance(terrain->get_world_position(0,1), terrain->get_world_position(0,0));
    Distance *= 1.5f;
    size_t j2 = 0; 
    if (rubberband) {
        while (j2 < Path.size()-1) {
           

            if (Vec3::Distance(Path[j2],Path[j2+1])>Distance) {
                Vec3 newPoint{ (Path[j2 + 1].x + Path[j2].x) / 2,(Path[j2 + 1].y + Path[j2].y) / 2,(Path[j2 + 1].z + Path[j2].z) / 2 };
                Path.insert(Path.begin()+j2+1,newPoint);
                
            }
            else {
                j2++;
            }
            

        }

    }
    
    for (size_t i = 0; i < Path.size(); i ++) {
        //if it is start node 
        if (i == 0 ) {
            for (size_t j = 0; j < 4; j ++) {

                if (j==0 ) {
                    newPath.push_back(Path[i]);
                }

                newPath.push_back(Vec3::CatmullRom(Path[i],Path[i],Path[i+1],Path[i+2], j *0.25f));
           
            }
            
        }

        //second last node
        else if (i == Path.size()-2) {
            for (size_t j = 0; j < 4; j++) {
                if (j == 0) {
                    newPath.push_back((Path[i]));
                }
                newPath.push_back(Vec3::CatmullRom(Path[i-1], Path[i], (Path[i + 1]), (Path[i + 1]), j * 0.25f));

            }
        }
        else if (i == Path.size()-1) {
            newPath.push_back((Path[i]));
        }
        else {
            for (size_t j = 0; j < 4; j++) {
                if (j == 0) {
                    newPath.push_back((Path[i]));
                }
                newPath.push_back(Vec3::CatmullRom((Path[i-1]), (Path[i]), (Path[i + 1]), (Path[i + 2]), j * 0.25f));
            }

        }

    }
    std::reverse(newPath.begin(), newPath.end());
    return newPath;

}
PathResult AStarPather::compute_path(PathRequest &request)
{
    float TempGx, TempFx, TempHx;
    GridPos Diff{ 0,0 };
    
    GridPos goal = terrain->get_grid_position(request.goal);
    GridPos start = terrain->get_grid_position(request.start);
    float distance = 0.0f;
    if (request.newRequest==true) {
        
        initializeMapSize();
        Diff.col = abs(goal.col - start.col);
        Diff.row = abs(goal.row - start.row);

        distance = CalcHeuristics(request.settings, Diff,start);

        MapPath[start.row][start.col].fx = distance * request.settings.weight; 
        MapPath[start.row][start.col].gx = 0; 
        MapPath[start.row][start.col].hx = distance;
        MapPath[start.row][start.col].parent = nullptr;
        MapPath[start.row][start.col].list = open;

        //push to open list
        NopenL.push_back(OpenIT{ distance,start.row,start.col });
        std::sort(NopenL.begin(), NopenL.end(), [](OpenIT& a, OpenIT& b) {return a.cost < b.cost; });
        if (request.settings.debugColoring) {
            terrain->set_color(start.row, start.col, Colors::Blue);
        }
        

    }

    while (!NopenL.empty()) {

        // set the iterator to begin at the first node of open list 
        //    TL == C.c - 1, C.r + 1
        //    T == C.c 0, C.r + 1
        //    TR == C.c + 1, C.r + 1
        //    L == C.c - 1, C.r 0
        //    ----------------------
        //    R == C.c + 1, C.r 0
        //    BL == C.c - 1, C.r - 1
        //    B == C.c 0, C.r - 1
        //    BR == C.c + 1, C.r - 1
        std::sort(NopenL.begin(), NopenL.end(), [](OpenIT& a, OpenIT& b) {return a.cost < b.cost; });
        OpenIT centernode = *NopenL.begin();
        NopenL.erase(NopenL.begin());
        
//////////////////////////////////////////// pushing in the path positions///////////////////////////////////////////////////
        if (isDest(centernode.row, centernode.col, goal)) {

            Node* tempNode = &MapPath[centernode.row][centernode.col];
       
            std::vector<GridPos> contain;std::vector<Vec3>SmoothPath;
            while ((tempNode->gridpos.col!=start.col || tempNode->gridpos.row != start.row)&&tempNode!=nullptr) {

                if (request.settings.rubberBanding==true||request.settings.smoothing==true) {
                    rubberband = true;
                    contain.push_back(tempNode->gridpos);
                }
                else {
                    request.path.push_front(terrain->get_world_position(tempNode->gridpos)); 
                }
                tempNode = tempNode->parent;
            }
            if (request.settings.smoothing == true && request.settings.rubberBanding == true) {
                contain.push_back(start);
                contain = rubberBanding(contain);
                SmoothPath = CalcCMRS(contain);
                for (size_t i = 0; i < SmoothPath.size(); i++) {
                    request.path.push_front(SmoothPath[i]);
                }

                //check for add in points ;

            }

            else if (request.settings.smoothing == true) {
                contain.push_back(start);
                SmoothPath = CalcCMRS(contain);
                for (size_t i = 0; i < SmoothPath.size(); i++) {
                    request.path.push_front(SmoothPath[i]);

                }

            }
            else if (request.settings.rubberBanding == true) {
                rubberband = true;
                contain.push_back(start);
                contain = rubberBanding(contain);
                for (size_t i = 0; i < contain.size(); i++) {
                    request.path.push_front(terrain->get_world_position(contain[i]));
                }

            }
            else {
                request.path.push_front(request.start);
            }

            return PathResult::COMPLETE;
        }
///////////////////////////////////////////////////////////////////////////////////////////////////////////


        //parent node on closed
        MapPath[centernode.row][centernode.col].list = closed;
        if (request.settings.debugColoring)
        terrain->set_color(centernode.row, centernode.col,Colors::Yellow);

        OpenIT search = centernode;
        //bool blocked=true;
        float addition = 0.0f;
        for (size_t i = 0; i < 8; i++) {
            search.row = -1; search.col = -1;
            //check neighbouring nodes 

            switch (i) {
            case 0:
                //bottom 
                if (centernode.row > 0) {
                    search.row = centernode.row - 1;
                    search.col = centernode.col;
                    
                    if (terrain->is_wall(MapPath[search.row][search.col].gridpos)) {
                        
                        continue;
                    }
                    addition = 1;

                }
                break;
            case 1:
                //top
                if (centernode.row < mapHeight - 1) {
                    search.row = centernode.row + 1;
                    search.col = centernode.col;
                    
                    if (terrain->is_wall(MapPath[search.row][search.col].gridpos)) {
                        
                        continue;
                    }
                    addition = 1;
                    
                }
                break;
            case 2:
                //left
                if (centernode.col > 0) {
                    search.row = centernode.row;
                    search.col = centernode.col - 1;
                    
                    if (terrain->is_wall(MapPath[search.row][search.col].gridpos)) {
                      
                        continue;
                    }
                    addition = 1;

                }
                break;
            case 3:
                //right
                if (centernode.col < mapWidth - 1) {
                    search.row = centernode.row;
                    search.col = centernode.col + 1;
                    
                    if (terrain->is_wall(MapPath[search.row][search.col].gridpos)) {
                        
                        continue;
                    }
                    addition = 1;

                }

                break;
            case 4:
                //botLeft
                if (centernode.col > 0 && centernode.row > 0) {
                    search.row = centernode.row - 1;
                    search.col = centernode.col - 1;
                    
                    if (terrain->is_wall(MapPath[search.row][search.col].gridpos)||
                        (terrain->is_wall(MapPath[search.row][centernode.col].gridpos)||
                         terrain->is_wall(MapPath[centernode.row][search.col].gridpos))) {
                        
                        continue;
                    }
                    addition = sqrtf(2.f);
                }

                break;
            case 5:
                //top left
                if (centernode.col > 0 && centernode.row < mapHeight - 1) {
                    search.col = centernode.col - 1;
                    search.row = centernode.row + 1;
                    
                    if (terrain->is_wall(MapPath[search.row][search.col].gridpos) || 
                        (terrain->is_wall(MapPath[search.row][centernode.col].gridpos) ||
                            terrain->is_wall(MapPath[centernode.row][search.col].gridpos))) {
                        continue;
                    }
                    addition = sqrtf(2.f);
                }
                break;

            case 6:
                //topRight
                if (centernode.col < mapWidth - 1 && centernode.row < mapHeight - 1) {
                    search.col = centernode.col + 1;
                    search.row = centernode.row + 1;
                    
                    if (terrain->is_wall(MapPath[search.row][search.col].gridpos) ||
                        (terrain->is_wall(MapPath[search.row][centernode.col].gridpos) ||
                            terrain->is_wall(MapPath[centernode.row][search.col].gridpos))) {
  
                        continue;
                    }
                    addition = sqrtf(2.f);

                }

                break;
            case 7:
                //bottom Right
                if (centernode.col < mapWidth - 1 && centernode.row > 0) {
                    search.col = centernode.col + 1;
                    search.row = centernode.row - 1;
                    
                    if (terrain->is_wall(MapPath[search.row][search.col].gridpos) ||
                          (terrain->is_wall(MapPath[search.row][centernode.col].gridpos) ||
                            terrain->is_wall(MapPath[centernode.row][search.col].gridpos))) {

                        continue;
                    }

                    addition = sqrtf(2.f);

                }
                break;
            default:
                continue;
                break;
            };
            if (search.row <0||search.col<0) continue;

            TempGx = TempFx = TempHx = 0;

            
            Diff.col = abs(goal.col - search.col);
            Diff.row = abs(goal.row - search.row);
            distance = CalcHeuristics(request.settings,Diff, start);
 
            TempGx = MapPath[centernode.row][centernode.col].gx + addition;
            TempHx = distance;
            TempFx = TempGx + TempHx * request.settings.weight;
            //check if its already closed
            if (MapPath[search.row][search.col].list == empty) {
                MapPath[search.row][search.col].list = open;
                NopenL.push_back(OpenIT{ TempFx,search.row, search.col });

                //set color to blue----open 
                if (request.settings.debugColoring) {
                    terrain->set_color(search.row, search.col, Colors::Blue);
                }
               

                //push in the values for Given Cost Total Cost and Heuristics Sost
                MapPath[search.row][search.col].fx = TempFx;
                MapPath[search.row][search.col].gx = TempGx;
                MapPath[search.row][search.col].hx = TempHx;
                MapPath[search.row][search.col].parent = &MapPath[centernode.row][centernode.col];
                
            }
            else {
                if (MapPath[search.row][search.col].fx > TempFx) {
                    if (MapPath[search.row][search.col].list == closed) {
                        MapPath[search.row][search.col].list = open;
                            MapPath[search.row][search.col].fx = TempFx;
                            MapPath[search.row][search.col].gx = TempGx;
                            MapPath[search.row][search.col].hx = TempHx;
                            MapPath[search.row][search.col].parent = &MapPath[centernode.row][centernode.col];
                            NopenL.push_back(OpenIT{ TempFx,search.row, search.col });

                            if (request.settings.debugColoring)
                            terrain->set_color(search.row, search.col, Colors::Blue);
                    }
                    else if (MapPath[search.row][search.col].list == open){
                        for (int i = 0; i < NopenL.size(); i ++) {
                            if (NopenL[i].col == search.col && NopenL[i].row == search.row) {
                                MapPath[search.row][search.col].fx = TempFx;
                                MapPath[search.row][search.col].gx = TempGx;
                                MapPath[search.row][search.col].hx = TempHx;
                                MapPath[search.row][search.col].parent = &MapPath[centernode.row][centernode.col];

                                NopenL.erase(NopenL.begin()+i);

                                NopenL.push_back(OpenIT{ TempFx,search.row, search.col });
                                if (request.settings.debugColoring)
                                terrain->set_color(search.row, search.col, Colors::Blue);

                                break;
                            }

                        }
                    }

                }
            }

        }
        if (request.settings.singleStep == true) {
            return PathResult::PROCESSING;
        }
    }
    /*
        This is where you handle pathing requests, each request has several fields:

        start/goal - start and goal world positions
        path - where you will build the path upon completion, path should be
            start to goal, not goal to start
        heuristic - which heuristic calculation to use
        weight - the heuristic weight to be applied
        newRequest - whether this is the first request for this path, should generally
            be true, unless single step is on

        smoothing - whether to apply smoothing to the path
        rubberBanding - whether to apply rubber banding
        singleStep - whether to perform only a single A* step
        debugColoring - whether to color the grid based on the A* state:
            closed list nodes - yellow
            open list nodes - blue

            use terrain->set_color(row, col, Colors::YourColor);
            also it can be helpful to temporarily use other colors for specific states
            when you are testing your algorithms

        method - which algorithm to use: A*, Floyd-Warshall, JPS+, or goal bounding,
            will be A* generally, unless you implement extra credit features

        The return values are:
            PROCESSING - a path hasn't been found yet, should only be returned in
                single step mode until a path is found
            COMPLETE - a path to the goal was found and has been built in request.path
            IMPOSSIBLE - a path from start to goal does not exist, do not add start position to path
    */

    // WRITE YOUR CODE HERE
    return PathResult::IMPOSSIBLE;
}
