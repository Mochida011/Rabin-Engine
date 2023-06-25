#pragma once
#include "Misc/PathfindingDetails.hpp"
#include <unordered_set>

enum onList { empty = 0, open, closed };

 struct Node{
     Node* parent;
     GridPos gridpos;
     float fx;
     float gx;
     float hx; 
     char list;
     char push;
     

};       


 struct OpenIT {
     float cost;
     int row;
     int col;

     //bool operator==(const OpenIT& other) const {
     //    return cost == other.cost;
     //}

 };


class AStarPather
{
public:
    /* 
        The class should be default constructible, so you may need to define a constructor.
        If needed, you can modify the framework where the class is constructed in the
        initialize functions of ProjectTwo and ProjectThree.
    */
    AStarPather();
    /* ************************************************** */
    // DO NOT MODIFY THESE SIGNATURES
    bool initialize();
    void shutdown();
    PathResult compute_path(PathRequest &request);
    /* ************************************************** */
    /*
        You should create whatever functions, variables, or classes you need.
        It doesn't all need to be in this header and cpp, structure it whatever way
        makes sense to you.
    */

    Node** MapPath;
    int mapWidth = 0;
    int mapHeight = 0;

    std::vector<OpenIT> NopenL;
    bool rubberband =false; 
    void initializeMapSize(void);
    float CalcHeuristics(PathRequest::Settings heuristic, GridPos PositionToUse, GridPos start);
    std::vector<GridPos> rubberBanding(std::vector<GridPos> arrayy);
    std::vector<Vec3> CalcCMRS(std::vector<GridPos>Path);

};