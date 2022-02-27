#ifndef __FUNC_H__
#define __FUNC_H__

#include "hgCircuit.h"

namespace HGR
{
    /*   Helper functions   */
    Net* get_net(int id);
    Pin* get_pin(int id);
    Cell* get_cell(int id);
    Layer* get_metal(int lNum);
    Layer* get_cut(int lNum);
    MacroVia* get_via(string type);
    Track* get_track(int id);
    Topology* get_topology(int id);
    Segment* get_segment(int netid, int segid);
    int get_track_index(int lNum, Rect<int> line);
    bool is_valid_via_type(string type);
    bool is_cut_layer(string layerName);
    bool is_metal_layer(string layerName);
    bool get_track_index(int lNum, Rect<int> line, int &trackid);
    bool get_track_index(int lNum, int dir, Point<int> _pt, int &trackid);
    bool get_tracks_on_line(int lNum, int dir, Rect<int> _line, vector<int> &_tracks);
    bool is_vertical(int lNum);
    bool is_horizontal(int lNum);
    bool is_preferred(int lNum, int direction);
    bool intersects(Point<int> _pt, Rect<int> _line);
    bool is_covered_by_pin(int pinid, Point<int> _pt);
    bool line_overlap(Rect<int> _line1, Rect<int> _line2);
    
    int line_overlap_length(Rect<int> _line1, Rect<int> _line2);    
    int nthreads();
    int direction(Point<int> pt1, Point<int> pt2);
    int direction(int x1, int y1, int x2, int y2);
    int preferred(int lNum);
    int non_preferred(int lNum);
    int die_width();
    int die_height();
    int num_layers();
    int num_tracks();
    int num_nets();
    int num_pins();
    int num_cells();
    int lef_unit_microns();
    int def_unit_microns();
    int wire_width(int lNum);
    int min_spacing(int lNum);
    int cut_spacing(int lNum);
    int min_area(int lNum);
    int min_length(int lNum);
    int run_length(int dir, Rect<int> _line1, Rect<int> _line2);
    int parallel_run_length_spacing(int lNum, int length, int width);
    int get_spacing(Rect<int> _shape1, Rect<int> _shape2, bool vertical);
    bool end_of_line_rule(int lNum, int &eolSpacing, int &eolWidth, int &eolWithin);
    bool end_of_line_rule_parallel_edge(int lNum, int &eolSpacing, int &eolWidth, int &eolWithin, int &parSpacing, int &parWithin);

    int end_of_line_spacing(int lNum);
    int end_of_line_within(int lNum);
    int distance(Point<int> _pt, Rect<int> _line);
    int manhattan_distance(Point<int> pt1, Point<int> pt2);
    int manhattan_distance(int x1, int y1, int x2, int y2);
    string benchName(); 
    bool remove(vector<int> &container, int elem);
    bool exist(vector<int> &container, int elem);
    bool exist(vector<pair<int,int>> &container, pair<int,int> elem);
    int lb(vector<int> &list, int elem);
    int ub(vector<int> &list, int elem);
    bool line_to_line_intersection(Point<int> ll1, Point<int> ur1, Point<int> ll2, Point<int> ur2, Point<int> &ptOut);
    bool track_to_track_intersection(int t1, int t2, Point<int> &_pt);
    bool pin_to_line_overlapping_intervals(int pinid, int lNum, Rect<int> _line, vector<Rect<int>> &_overlaps);
    bool pin_to_line_overlapping_boundary(int pinid, int lNum, Rect<int> _line, Point<int> &ll, Point<int> &ur);
    double pin_to_pin_distance(int p1, int p2);
    // ????
    template <typename A>  bool remove(vector<A>& container, const A& elem);
    
    // For parsing & initialize
    int delta_x(Point<int> orig, Rect<int> rect);
    int delta_y(Point<int> orig, Rect<int> rect);
    void get_orient(string orient, int &rotate, bool &flip);
    void shift_to_origin(int dx, int dy, Rect<int> rect1, Rect<int> &rect2);
    void flip_or_rotate(Point<int> orig, Rect<int> rect1, Rect<int> &rect2, int rotate, bool flip);


    // For boost geometry
    box convert(Rect<int> rect);
    pt convert(Point<int> point);
    polygon to_polygon(Rect<int> rect);
    multi_polygon convert(vector<Rect<int>> rects);
    Rect<int> buffer(Rect<int> rect, int buffer_distance);
    Rect<int> buffer(Rect<int> rect, int buffer_horizontal, int buffer_vertical);
    Rect<int> convert(box b);
    Point<int> convert(pt p);
    Rect<int> overlaps(Rect<int> rect1, Rect<int> rect2);
    int area(Rect<int> rect1, Rect<int> rect2);
    int area(Rect<int> rect);

    Rect<int> get_pin_to_pin_interval(int p1, int p2, int trackid);
    //
    dense_hash_map<int,multi_polygon> guide_map(int netid);
    dense_hash_map<int,multi_polygon> buffered_guide_map(int netid, double buffer_distance);

    void set_resolution(int &v);
    // Util functions
    void create_plot(int netid);
    void create_congestion_map(int lNum);

    string get_macro_via(int l1, int d1, int l2, int d2);
};

#endif
