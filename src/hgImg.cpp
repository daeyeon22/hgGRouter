#include "hgRouter.h"
#include "hgCircuit.h"
#include "hgImg.h"

using namespace HGR;

svg::Color convert_cap_to_color(int cap, int assigned);

svg::Polygon& operator << (svg::Polygon& shape, Rect<int> rect)
{

    shape << svg::Point(rect.ll.x, rect.ll.y) << svg::Point(rect.ll.x, rect.ur.y) << svg::Point(rect.ur.x, rect.ur.y) << svg::Point(rect.ur.x, rect.ll.y);
    return shape;
}

/*
svg::Line& operator << (svg::Line& shape, Rect<int> rect)
{
    line << svg::Point(rect.ll.x, rect.ll.y) << svg::Point(rect.ur.x, rect.ur.y);
    return line;
}
*/

void HGR::create_plot(int _net)
{
   

    //cout << "Create Plot" << endl;

    Net* curNet = get_net(_net);
    string fileName = "../img/" + ckt->benchName + "/" + curNet->name + ".svg";
    
    svg::Dimensions dimensions( die_width() + ckt->dieArea.ll.x*2, die_height() + ckt->dieArea.ll.y*2 );
    svg::Document doc(fileName, svg::Layout(dimensions, svg::Layout::BottomLeft, 0.5));

    svg::Color colors[] 
        = { svg::Color::Red, svg::Color::Orange, svg::Color::Yellow, svg::Color::Green, svg::Color::Blue, svg::Color::Purple, svg::Color::Black };


    svg::Polygon border(svg::Color::White, svg::Stroke(40, svg::Color::Black));
    
    border << ckt->dieArea; 
    doc << border;

    cout << "plot : " << fileName << endl;
    
    for(size_t i=0; i < curNet->guides.size(); i++)
    {
        int lNum = curNet->guides[i].first;
        Rect<int> rect = curNet->guides[i].second;

        svg::Polygon shape(svg::Fill(colors[lNum], 0.25), svg::Stroke(5.0, svg::Color::Blue));
        shape << rect;
        doc << shape;
    }

    // Print grids
    for(int i=0; i < grid->numCols + 1; i++)
    {
        int x1 = grid->xOffsets[i];
        //grid->area.ll.x + grid->GCwidth * i;
        int x2 = grid->xOffsets[i];
        //int x2 = grid->area.ll.x + grid->GCwidth * i;
        int y1 = grid->area.ll.y;
        int y2 = grid->area.ur.y;

        doc << svg::Line(svg::Point(x1, y1), svg::Point(x2, y2), svg::Stroke(15.0, svg::Color::Black));
    }
    
    for(int j=0; j < grid->numRows + 1; j++)
    {
        int y1 = grid->yOffsets[j]; //grid->area.ll.y + grid->GCheight * j;
        int y2 = grid->yOffsets[j]; //grid->area.ll.y + grid->GCheight * j;
        int x1 = grid->area.ll.x;
        int x2 = grid->area.ur.x;

        doc << svg::Line(svg::Point(x1, y1), svg::Point(x2, y2), svg::Stroke(15.0, svg::Color::Black));
    }


    /*
    for(int i=0; i < num_tracks(); i++)
    {
        Track* track = get_track(i);
        

        int x1 = get_track(i)->ll.x;
        int y1 = get_track(i)->ll.y;
        int x2 = get_track(i)->ur.x;
        int y2 = get_track(i)->ur.y;
        int lNum = get_track(i)->layer;
        doc << svg::Line(svg::Point(x1, y1), svg::Point(x2, y2), svg::Stroke(10.0, colors[lNum]));
    }
    */

    // Print pins
    for(size_t i=0; i < curNet->terminals.size(); i++)
    {
        Pin* curPin = get_pin(curNet->terminals[i]);
        
        for(size_t j=0; j < curPin->rects.size(); j++)
        {
            int lNum = curPin->rects[j].first;
            Rect<int> rect = curPin->rects[j].second;

            svg::Polygon shape(svg::Fill(colors[lNum], 0.7), svg::Stroke(5.0, svg::Color::Black));
            shape << rect;
            doc << shape;
        }
    }

    // Print gcells
    Topology* tp = get_topology(_net);

    for(size_t i=0; i < tp->segments.size(); i++)
    {
        Segment* s = get_segment(_net, i);
        int layer = s->layer;
        int xl, yl, xh, yh;
        
        Gcell* g1 = grid->gcell(s->g1);
        Gcell* g2 = grid->gcell(s->g2);

        xl = min(g1->rect.ll.x, g2->rect.ll.x);
        yl = min(g1->rect.ll.y, g2->rect.ll.y);
        xh = max(g1->rect.ur.x, g2->rect.ur.x);
        yh = max(g1->rect.ur.y, g2->rect.ur.y);

        svg::Polygon shape(svg::Fill(colors[layer], 0.7), svg::Stroke(20.0, svg::Color::Red));
        Rect<int> rect(xl, yl, xh, yh);
        shape << rect;
        doc << shape;

    }

    /*
    for(size_t i=0; i < rou->topologies[_net].gcells.size(); i++)
    {
        int gcellid = rou->topologies[_net].gcells[i];
        int lNum = grid->gcell(gcellid)->z;
        Rect<int> rect = grid->gcell(gcellid)->rect;

        svg::Polygon shape(svg::Fill(colors[lNum], 0.7), svg::Stroke(5.0, svg::Color::Black));
        shape << rect;
        doc << shape;
    }
    */

#ifdef ROUTED
    // Print segments
    for(size_t i=0; i < rou->topologies[_net].segments.size(); i++)
    {
        Segment* s = &rou->topologies[_net].segments[i];
        Gcell* g1 = grid->gcell(s->g1);
        Gcell* g2 = grid->gcell(s->g2);

        //if(s->access) continue;
        //
       
        for(size_t j=0; j < s->lines.size(); j++)
        {
            int lNum = s->layers[j];
            Rect<int> bbox = s->lines[j];
            
            int halfWidth = wire_width(lNum) / 2;
            bbox.ll.x -= halfWidth; 
            bbox.ll.y -= halfWidth; 
            bbox.ur.x += halfWidth; 
            bbox.ur.y += halfWidth; 
            svg::Polygon shape(svg::Fill(colors[lNum], 0.7), svg::Stroke(30.0, svg::Color::Black));
            shape << bbox;
            doc << shape;
        }
      
        for(size_t j=0; j < s->pins.size(); j++)
        {
            Ext* _ext = &s->extension[s->pins[j]];
            for(size_t k=0; k < _ext->lines.size(); k++)
            {
                int lNum = _ext->layers[k];
                Rect<int> bbox = _ext->lines[k];

                int halfWidth = wire_width(lNum) / 2;
                bbox.ll.x -= halfWidth; 
                bbox.ll.y -= halfWidth; 
                bbox.ur.x += halfWidth; 
                bbox.ur.y += halfWidth; 
                svg::Polygon shape(svg::Fill(colors[lNum], 0.7), svg::Stroke(30.0, svg::Color::Black));
                shape << bbox;
                doc << shape;
            }
        }

        /*
        if(s->track != INT_MAX)
        {
        int lNum = s->layer;
        int x1 = (s->direction == VERTICAL) ? get_track(s->track)->ll.x : min(g1->rect.ll.x, g2->rect.ll.x);
        int x2 = (s->direction == VERTICAL) ? get_track(s->track)->ur.x : max(g1->rect.ur.x, g2->rect.ur.x);
        int y1 = (s->direction == VERTICAL) ? min(g1->rect.ll.y, g2->rect.ll.y) : get_track(s->track)->ll.y;
        int y2 = (s->direction == VERTICAL) ? max(g1->rect.ur.y, g2->rect.ur.y) : get_track(s->track)->ur.y;
        //doc << svg::Line(svg::Point(x1, y1), svg::Point(x2, y2), svg::Stroke(30.0, colors[lNum])); //svg::Color::Black));
        //doc << svg::Circle(svg::Point(x1, y1), 200, colors[lNum], svg::Stroke(30.0, svg::Color::Black));
        //doc << svg::Circle(svg::Point(x2, y2), 200, colors[lNum], svg::Stroke(30.0, svg::Color::Black));
        int halfWidth = wire_width(lNum) / 2;
        x1 -= halfWidth; 
        y1 -= halfWidth; 
        x2 += halfWidth; 
        y2 += halfWidth; 
        //int x1 = min(g1->rect.ll.x, g2->rect.ll.x);
        //int x2 = max(g1->rect.ur.x, g2->rect.ur.x);
        //int y1 = min(g1->rect.ll.y, g2->rect.ll.y);
        //int y2 = max(g1->rect.ur.y, g2->rect.ur.y);
        Rect<int> rect(x1, y1, x2, y2);
        svg::Polygon shape(svg::Fill(colors[lNum], 0.7), svg::Stroke(30.0, svg::Color::Black));
        shape << rect;
        doc << shape;
        }
        */
        //*/
        /*
        int halfWidth = wire_width(s->layer);
        Rect<int> rect(s->ll, s->ur);
        rect.ll.x -= (s->direction == VERTICAL) ? halfWidth : 0;
        rect.ll.y -= (s->direction == VERTICAL) ? 0 : halfWidth;
        rect.ur.x += (s->direction == VERTICAL) ? halfWidth : 0;
        rect.ur.y += (s->direction == VERTICAL) ? 0 : halfWidth;
        */


    }
#endif

    doc.save();
    //cout << "Plot Geneartion Successfully Finished" << endl;
}


void HGR::create_congestion_map(int lNum)
{
    string fileName = "../img/" + ckt->benchName + "/" + get_metal(lNum)->name + ".svg";
    
    svg::Dimensions dimensions( die_width() + ckt->dieArea.ll.x*2, die_height() + ckt->dieArea.ll.y*2 );
    svg::Document doc(fileName, svg::Layout(dimensions, svg::Layout::BottomLeft, 1));

    svg::Color colors[] 
        = { svg::Color::Red, svg::Color::Orange, svg::Color::Yellow, svg::Color::Green, svg::Color::Blue, svg::Color::Purple, svg::Color::Black };


    svg::Polygon border(svg::Color::White, svg::Stroke(40, svg::Color::Black));
    border << ckt->dieArea; 
    doc << border;

    cout << "plot : " << fileName << endl;
 
    // Print gcells
    for(size_t i=0; i < grid->gcells.size(); i++)
    {
        svg::Polygon shape(convert_cap_to_color(grid->gcells[i].edgeCap, grid->history[i]), svg::Stroke(15.0, svg::Color::Black));
        shape << grid->gcells[i].rect;
        doc << shape;
    }
    

    doc.save();
}

svg::Color convert_cap_to_color(int cap, int assigned){
    int r, g, b;
    double ratio = 1.0*(cap - assigned)/cap;
    if( ratio > 0.7 )       r = 255, g = 255, b = 255;
    else if( ratio > 0.5 )  r = 220, g = 220, b = 220;
    else if( ratio > 0.3 )  r = 128, g = 128, b = 128;
    else if( ratio > 0.0 )  r = 105, g = 105, b = 105;
    else if( ratio == 0.0 ) r = 0, g = 0, b = 0;
    else                    r = 255, g = 0, b = 0;
    return svg::Color(r,g,b);
}
