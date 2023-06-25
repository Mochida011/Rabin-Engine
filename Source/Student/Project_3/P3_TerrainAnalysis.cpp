#include <pch.h>
#include "Terrain/TerrainAnalysis.h"
#include "Terrain/MapMath.h"
#include "Agent/AStarAgent.h"
#include "Terrain/MapLayer.h"
#include "Projects/ProjectThree.h"

#include <iostream>

bool ProjectThree::implemented_fog_of_war() const // extra credit
{
    return false;
}

float distance_to_closest_wall(int row, int col)
{
    /*
        Check the euclidean distance from the given cell to every other wall cell,
        with cells outside the map bounds treated as walls, and return the smallest
        distance.  Make use of the is_valid_grid_position and is_wall member
        functions in the global terrain to determine if a cell is within map bounds
        and a wall, respectively.
    */
    //float givenDistance = sqrt((float)(row * row + col * col));
    float minDistance = FLT_MAX;
    for (int i = 0; i < terrain->get_map_height(); i ++) {

        for (int j = 0; j < terrain->get_map_width(); j ++) {


            if (terrain->is_valid_grid_position(i, j)&&(terrain->is_wall(i, j))) {
                float distance = sqrt(float((j - col)*(j - col))+float((i - row)*(i - row)));
                minDistance = distance<minDistance?distance:minDistance;

            }
            else if (terrain->is_valid_grid_position(i,j)&&(i == 0 || j == 0||j==terrain->get_map_height()-1||i ==terrain->get_map_width()-1)) {
                if (i==0) {
                    float distance = sqrt(float((j - col) * (j - col)) + float((i - 1 - row) * (i - 1 - row)));
                    minDistance = distance < minDistance ? distance : minDistance;

                }
                else if (j==0) {
                    float distance = sqrt(float((j - 1 - col) * (j - 1 - col)) + float((i -  row) * (i -  row)));
                    minDistance = distance < minDistance ? distance : minDistance;
                }
                else if (j==terrain->get_map_width()-1) {
                    float distance = sqrt(float((j + 1 - col) * (j + 1 - col)) + float((i - row) * (i - row)));
                    minDistance = distance < minDistance ? distance : minDistance;
                }
                else if (i==terrain->get_map_height()-1) {
                    float distance = sqrt(float((j - col) * (j - col)) + float((i + 1 - row) * (i + 1 - row)));
                    minDistance = distance < minDistance ? distance : minDistance;

                }
            }

        }
    }
    //euclidean distance offset from given cell to wall cell 
    //sqrt (A^2+B^2)


    //return smallest distance 

    //use valid grid position, is wall member in global terrain to
    //determine if cell is within map bounds and wall


    // WRITE YOUR CODE HERE
    return minDistance; // REPLACE THIS
}

bool is_clear_path(int row0, int col0, int row1, int col1)
{
    /*
        Two cells (row0, col0) and (row1, col1) are visible to each other if a line
        between their centerpoints doesn't intersect the four boundary lines of every
        wall cell.  You should puff out the four boundary lines by a very tiny amount
        so that a diagonal line passing by the corner will intersect it.  Make use of the
        line_intersect helper function for the intersection test and the is_wall member
        function in the global terrain to determine if a cell is a wall or not.
    */

    //Two cells(row0, col0) and (row1, col1) are visible to each other

    
    //std::cout << centerpointx << std::endl;
    int minrow, mincol, maxrow, maxcol;
    minrow = std::min(row0,row1);
    mincol = std::min(col0,col1);
    maxrow = std::max(row0,row1);
    maxcol = std::max(col0,col1);
    for (int i = minrow; i <= maxrow; i ++) {
        for (int j = mincol; j <= maxcol; j ++) {
            //Vec3 currentposition = terrain->get_world_position(i,j);

            if (terrain->is_wall(i,j)) {
                float maxx = (float)j + 0.501f;
                float maxy = (float)i + 0.501f;
                float minx = (float)j - 0.501f;
                float miny = (float)i - 0.501f;
                if (line_intersect(Vec2((float)col0, (float)row0), Vec2((float)col1, (float)row1), Vec2(minx, miny), Vec2(maxx, miny)) || 
                    line_intersect(Vec2((float)col0, (float)row0), Vec2((float)col1, (float)row1), Vec2(minx, miny), Vec2(minx, maxy)) ||
                    line_intersect(Vec2((float)col0, (float)row0), Vec2((float)col1, (float)row1), Vec2(minx, maxy), Vec2(maxx, maxy)) ||
                    line_intersect(Vec2((float)col0, (float)row0), Vec2((float)col1, (float)row1), Vec2(maxx, maxy), Vec2(maxx, miny))) 
                    return false;
                
            }
        }
    }

    // WRITE YOUR CODE HERE

    return true; // REPLACE THIS
}

void analyze_openness(MapLayer<float> &layer)
{
    /*
        Mark every cell in the given layer with the value 1 / (d * d),
        where d is the distance to the closest wall or edge.  Make use of the
        distance_to_closest_wall helper function.  Walls should not be marked.
    */

    for (int i = 0; i < terrain->get_map_height(); i ++) {
        for (int j = 0; j < terrain->get_map_width(); j ++) {
            GridPos Temp{ i, j };
            if (distance_to_closest_wall(i, j)!=FLT_MAX&&!terrain->is_wall(i,j)) {
                float markValue = 1.f;              
                markValue = 1.f / ((float)(distance_to_closest_wall(i, j) * distance_to_closest_wall(i, j)));

                layer.set_value(Temp, markValue);
                
            }
        }
    }

    // WRITE YOUR CODE HERE
}

void analyze_visibility(MapLayer<float> &layer)
{
    /*
        Mark every cell in the given layer with the number of cells that
        are visible to it, divided by 160 (a magic number that looks good).  Make sure
        to cap the value at 1.0 as well.

        Two cells are visible to each other if a line between their centerpoints doesn't
        intersect the four boundary lines of every wall cell.  Make use of the is_clear_path
        helper function.
    */


    for (int i = 0; i < terrain->get_map_height(); i ++) {
        for (int j = 0; j < terrain->get_map_width(); j ++) {
            if (!terrain->is_wall(i,j)) {
                int visiblecount = 0;
                for (int k = 0; k < terrain->get_map_height(); k++) {
                    for (int l = 0; l < terrain->get_map_width(); l++) {
                        if (is_clear_path(i,j,k,l)&&!terrain->is_wall(k,l)) {
                            visiblecount++;
                        }
                    }
                }

                float magic = visiblecount / 160.f;
                magic = magic > 1.0f ? 1.0f : magic;
                layer.set_value(i,j,magic);

            }
        }
    }

    // WRITE YOUR CODE HERE
}

void analyze_visible_to_cell(MapLayer<float> &layer, int row, int col)
{
    /*
        For every cell in the given layer mark it with 1.0
        if it is visible to the given cell, 0.5 if it isn't visible but is next to a visible cell,
        or 0.0 otherwise.

        Two cells are visible to each other if a line between their centerpoints doesn't
        intersect the four boundary lines of every wall cell.  Make use of the is_clear_path
        helper function.
    */

   
    for (int i = 0; i < terrain->get_map_height(); i ++) {
        for (int j = 0; j < terrain->get_map_width(); j ++) {
            GridPos Temp{ i,j };

            if (!terrain->is_wall(i, j)) {
                if (is_clear_path(row, col, i, j)) {

                    layer.set_value(Temp, 1.f);
                }
                else {
                    layer.set_value(Temp, 0.f);
                }
            }
        }
    }

    for (int i = 0; i < terrain->get_map_height(); i ++) {
        for (int j = 0; j < terrain->get_map_width(); j ++) {
            if (layer.get_value(i,j)==0.f&&!terrain->is_wall(i,j)) {
                if (i!=terrain->get_map_height() - 1) {
                    if (layer.get_value(i+1,j)==1.f&& !terrain->is_wall(i+1, j)) {
                        layer.set_value(i,j,0.5f);
                    }
                }
                if (j!=terrain->get_map_width()-1) {
                    if (layer.get_value(i,j+1)==1.f&& !terrain->is_wall(i, j+1)) {
                        layer.set_value(i,j,0.5);
                    }
                }
                if (i!=0) {
                    if (layer.get_value(i-1,j) ==1.f&& !terrain->is_wall(i-1, j)) {
                        layer.set_value(i, j, 0.5);
                    }
                }
                if (j!=0) {
                    if (layer.get_value(i, j-1) ==1.f&&!terrain->is_wall(i, j-1)) {
                        layer.set_value(i , j, 0.5);
                    }
                }
                if (j != 0&& i != 0) {
                    if (layer.get_value(i-1, j - 1)==1.f&& !terrain->is_wall(i-1, j-1)&&
                        !terrain->is_wall(i-1,j)&&!terrain->is_wall(i,j-1)) {
                        layer.set_value(i, j, 0.5f);
                    }

                }
                if (j != terrain->get_map_width() - 1 && i != terrain->get_map_height() - 1) {
                    if (layer.get_value(i + 1, j + 1)==1.f&& !terrain->is_wall(i+1, j+1) && !terrain->is_wall(i+1,j)&&
                        !terrain->is_wall(i,j+1)) {
                        layer.set_value(i , j , 0.5f);
                    }
                }
                if (j != 0 && i != terrain->get_map_height() - 1) {
                    if (layer.get_value(i + 1, j - 1) == 1.f && !terrain->is_wall(i + 1, j - 1)&&
                        !terrain->is_wall(i,j-1)&&
                        !terrain->is_wall(i+1,j)) {
                        layer.set_value(i, j, 0.5f);
                    }
                }
                if (j != terrain->get_map_width() - 1 && i != 0) {
                    if (layer.get_value(i - 1, j + 1) == 1.f && !terrain->is_wall(i - 1, j + 1)&&
                        !terrain->is_wall(i-1,j)&&!terrain->is_wall(i,j+1)) {
                        layer.set_value(i, j, 0.5f);
                    }
                }

            }
        }
    }

    // WRITE YOUR CODE HERE
}

void analyze_agent_vision(MapLayer<float> &layer, const Agent *agent)
{
    /*
        For every cell in the given layer that is visible to the given agent,
        mark it as 1.0, otherwise don't change the cell's current value.

        You must consider the direction the agent is facing.  All of the agent data is
        in three dimensions, but to simplify you should operate in two dimensions, the XZ plane.

        Take the dot product between the view vector and the vector from the agent to the cell,
        both normalized, and compare the cosines directly instead of taking the arccosine to
        avoid introducing floating-point inaccuracy (larger cosine means smaller angle).

        Give the agent a field of view slighter larger than 180 degrees.

        Two cells are visible to each other if a line between their centerpoints doesn't
        intersect the four boundary lines of every wall cell.  Make use of the is_clear_path
        helper function.
    */
    
    Vec3 viewvector = agent->get_forward_vector();
    viewvector.Normalize();
    float FOV = cos(float((95.f * M_PI) / 180.f));
    
    for (int i = 0; i < terrain->get_map_height(); i++) {
        for (int j = 0; j < terrain->get_map_width(); j++) {
            int col = terrain->get_grid_position(agent->get_position()).col;
            int row = terrain->get_grid_position(agent->get_position()).row;
            if (is_clear_path(row,col,i,j)&&!terrain->is_wall(i,j)) {
                
                Vec2 Product{ viewvector.x,viewvector.z };
                Vec3 movingVec = terrain->get_world_position(i,j)- agent->get_position();
                movingVec.Normalize();
                
                float prod = Product.Dot(Vec2(movingVec.x,movingVec.z));
                if (prod >FOV)
                    layer.set_value(i, j, 1.f);

            }
            
        }

    }
    // WRITE YOUR CODE HERE
}

void propagate_solo_occupancy(MapLayer<float> &layer, float decay, float growth)
{
    /*
        For every cell in the given layer:

            1) Get the value of each neighbor and apply decay factor
            2) Keep the highest value from step 1
            3) Linearly interpolate from the cell's current value to the value from step 2
               with the growing factor as a coefficient.  Make use of the lerp helper function.
            4) Store the value from step 3 in a temporary layer.
               A float[40][40] will suffice, no need to dynamically allocate or make a new MapLayer.

        After every cell has been processed into the temporary layer, write the temporary layer into
        the given layer;
    */
    float temp[40][40]{ 0.f };
    for (int i = 0; i < terrain->get_map_height(); i ++) {
        for (int j = 0; j < terrain->get_map_width(); j++) {
            float highestValue = -FLT_MIN; 
            if (!terrain->is_wall(i, j)) {
                if (i != terrain->get_map_height() - 1) {    
                    if (!terrain->is_wall(i + 1, j)) {
                        
                        float newInfluence = layer.get_value(i + 1, j) * exp(-1 * 1 * decay);
                        highestValue = std::max(highestValue, newInfluence);  
                    }

                }
                if (j != terrain->get_map_width() - 1) {
                    if (!terrain->is_wall(i, j + 1)) {

                        float newInfluence = layer.get_value(i , j+1) * exp(-1 * 1 * decay);
                        highestValue = std::max(highestValue, newInfluence);
                    }

                }
                if (i != 0) {
                    if (!terrain->is_wall(i - 1, j)) {

                        float newInfluence = layer.get_value(i-1, j ) * exp(-1 * 1 * decay);
                        highestValue = std::max(highestValue, newInfluence);
                       
                    }
                }
                if (j != 0) {
                    if ( !terrain->is_wall(i, j - 1)) {
                        float newInfluence = layer.get_value(i, j-1) * exp(-1 * 1 * decay);
                        highestValue = std::max(highestValue, newInfluence);
                    }
                }
                if (j != 0 && i != 0) {
                    if (!terrain->is_wall(i - 1, j - 1) &&
                        !terrain->is_wall(i - 1, j) && !terrain->is_wall(i, j - 1)) {
                        float newInfluence = layer.get_value(i - 1, j-1) * exp(-1 * sqrt(2.f) * decay);
                        highestValue = std::max(highestValue, newInfluence);
                    }

                }
                if (j != terrain->get_map_width() - 1 && i != terrain->get_map_height() - 1) {
                    if (!terrain->is_wall(i + 1, j + 1) && !terrain->is_wall(i + 1, j) &&
                        !terrain->is_wall(i, j + 1)) {
                        float newInfluence = layer.get_value(i +1, j+1) * exp(-1 * sqrt(2.f) * decay);
                        highestValue = std::max(highestValue, newInfluence);
                    }
                }
                if (j != 0 && i != terrain->get_map_height() - 1) {
                    if (!terrain->is_wall(i + 1, j - 1) &&
                        !terrain->is_wall(i, j - 1) &&
                        !terrain->is_wall(i + 1, j)) {
                        float newInfluence = (float)(layer.get_value(i +1, j-1) * exp(-1 * sqrt(2) * decay));
                        highestValue = std::max(highestValue, newInfluence);
                    }       
                }
                if (j != terrain->get_map_width() - 1 && i != 0) {
                    if (!terrain->is_wall(i - 1, j + 1) &&
                        !terrain->is_wall(i - 1, j) && !terrain->is_wall(i, j + 1)) {
                        float newInfluence = (float)(layer.get_value(i - 1, j+1) * exp(-1 * sqrt(2) * decay));
                        highestValue = std::max(highestValue, newInfluence);
                    }
                }

            }
            temp[i][j]=lerp(layer.get_value(i,j), highestValue, growth);
        }
    }
    for (int i = 0; i < terrain->get_map_height(); i ++) {
        for (int j = 0; j < terrain->get_map_width(); j++) {
            layer.set_value(i,j,temp[i][j]);
        }
    }
    
    // WRITE YOUR CODE HERE
}

//no need
void propagate_dual_occupancy(MapLayer<float> &layer, float decay, float growth)
{
    /*
        Similar to the solo version, but the values range from -1.0 to 1.0, instead of 0.0 to 1.0

        For every cell in the given layer:

        1) Get the value of each neighbor and apply decay factor
        2) Keep the highest ABSOLUTE value from step 1
        3) Linearly interpolate from the cell's current value to the value from step 2
           with the growing factor as a coefficient.  Make use of the lerp helper function.
        4) Store the value from step 3 in a temporary layer.
           A float[40][40] will suffice, no need to dynamically allocate or make a new MapLayer.

        After every cell has been processed into the temporary layer, write the temporary layer into
        the given layer;
    */

    // WRITE YOUR CODE HERE
}

void normalize_solo_occupancy(MapLayer<float> &layer)
{
    /*
        Determine the maximum value in the given layer, and then divide the value
        for every cell in the layer by that amount.  This will keep the values in the
        range of [0, 1].  Negative values should be left unmodified.
    */
    float highestvalue=-FLT_MIN; 
    for (int i = 0; i < terrain->get_map_height(); i ++) {
        for (int j = 0; j < terrain->get_map_width(); j ++) {
            highestvalue = std::max(highestvalue, layer.get_value(i,j));
        }
    }
    for (int i = 0; i < terrain->get_map_height(); i++) {
        for (int j = 0; j < terrain->get_map_width(); j++) {
            if (layer.get_value(i,j)>0) {
                layer.set_value(i, j, layer.get_value(i, j) / highestvalue);
            }
            
        }
    }



    // WRITE YOUR CODE HERE
}

void normalize_dual_occupancy(MapLayer<float> &layer)
{
    /*
        Similar to the solo version, but you need to track greatest positive value AND 
        the least (furthest from 0) negative value.

        For every cell in the given layer, if the value is currently positive divide it by the
        greatest positive value, or if the value is negative divide it by -1.0 * the least negative value
        (so that it remains a negative number).  This will keep the values in the range of [-1, 1].
    */

    // WRITE YOUR CODE HERE
}

void enemy_field_of_view(MapLayer<float> &layer, float fovAngle, float closeDistance, float occupancyValue, AStarAgent *enemy)
{
    /*
        First, clear out the old values in the map layer by setting any negative value to 0.
        Then, for every cell in the layer that is within the field of view cone, from the
        enemy agent, mark it with the occupancy value.  Take the dot product between the view
        vector and the vector from the agent to the cell, both normalized, and compare the
        cosines directly instead of taking the arccosine to avoid introducing floating-point
        inaccuracy (larger cosine means smaller angle).

        If the tile is close enough to the enemy (less than closeDistance),
        you only check if it's visible to enemy.  Make use of the is_clear_path
        helper function.  Otherwise, you must consider the direction the enemy is facing too.
        This creates a radius around the enemy that the player can be detected within, as well
        as a fov cone.
    */

    // clear out old values setting any negative value to 0
    for (int i = 0; i < terrain->get_map_height(); i ++) {
        for (int j = 0; j < terrain->get_map_width(); j ++) {
            if (layer.get_value(i,j)<0)
                layer.set_value(i,j,0);
        }
    }

    Vec3 viewvector = enemy->get_forward_vector();
    viewvector.Normalize();
    
    float FOV = cos(float(((fovAngle / 2) * M_PI) / 180.f));

    //for every cell in field cone mark with occupancy value
    for (int i = 0; i < terrain->get_map_height(); i++) {
        for (int j = 0; j < terrain->get_map_width(); j++) {
            int col = terrain->get_grid_position(enemy->get_position()).col;
            int row = terrain->get_grid_position(enemy->get_position()).row;
            //if distance betweeen enemy and player is less than close distance, check for clear path and apply occupancy value
            if (Vec3::Distance(terrain->get_world_position(i, j), enemy->get_position()) < closeDistance) {
                GridPos enemypos =terrain->get_grid_position(enemy->get_position());
                if (is_clear_path(enemypos.row, enemypos.col, i,j)&&!terrain->is_wall(i,j))
                    layer.set_value(i, j, occupancyValue);

            }
            //else check for if it is within cone
            if (is_clear_path(row, col, i, j) && !terrain->is_wall(i, j)) {

                Vec2 Product{ viewvector.x,viewvector.z };
                Vec3 movingVec = terrain->get_world_position(i, j) - enemy->get_position();
                movingVec.Normalize();

                float prod = Product.Dot(Vec2(movingVec.x, movingVec.z));
                if (prod > FOV)
                    layer.set_value(i, j, occupancyValue);


            }

        }

    }

    // WRITE YOUR CODE HERE
}

bool enemy_find_player(MapLayer<float> &layer, AStarAgent *enemy, Agent *player)
{
    /*
        Check if the player's current tile has a negative value, ie in the fov cone
        or within a detection radius.
    */

    const auto &playerWorldPos = player->get_position();

    const auto playerGridPos = terrain->get_grid_position(playerWorldPos);

    // verify a valid position was returned
    if (terrain->is_valid_grid_position(playerGridPos) == true)
    {
        if (layer.get_value(playerGridPos) < 0.0f)
        {
            return true;
        }
    }

    // player isn't in the detection radius or fov cone, OR somehow off the map
    return false;
}

bool enemy_seek_player(MapLayer<float> &layer, AStarAgent *enemy)
{
    /*
        Attempt to find a cell with the highest nonzero value (normalization may
        not produce exactly 1.0 due to floating point error), and then set it as
        the new target, using enemy->path_to.

        If there are multiple cells with the same highest value, then pick the
        cell closest to the enemy.

        Return whether a target cell was found.
    */
    float highestvalue = -FLT_MIN; 
    int highrow, highcol;
    highrow = highcol = 0;
    for (int i = 0; i < terrain->get_map_height(); i ++) {
        for (int j = 0; j < terrain->get_map_width(); j++) {
            if (highestvalue<layer.get_value(i,j)) {
                highestvalue = layer.get_value(i, j);
                highrow = i; highcol = j;
            }

        }
    }
    enemy->path_to(terrain->get_world_position(highrow,highcol));

    // WRITE YOUR CODE HERE

    return false; // REPLACE THIS
}
