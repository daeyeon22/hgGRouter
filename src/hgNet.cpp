
#include "hgCircuit.h"
#include "hgRouter.h"
#include "hgTypeDef.h"
#include <boost/format.hpp>

bool HGR::Net::is_routed()
{
    return get_topology(id)->routed;
}


bool HGR::Net::is_single_pin()
{
    return terminals.size() == 1 ? true : false;
}

bool HGR::Net::is_double_pin()
{
    return terminals.size() == 2 ? true : false;
}

bool HGR::Net::is_multi_pin()
{
    return terminals.size() > 2 ? true : false;
}

void HGR::Net::get_routing_space(int _bufferDistance, set<int> &_rSpace)
{

    int xl = INT_MAX;
    int yl = INT_MAX;
    int xh = INT_MIN;
    int yh = INT_MIN;
    int ll = num_layers();
    int lh = 0;
    
    for(auto pinid : terminals)
    {
        Pin* pin = get_pin(pinid);

        for(auto it : pin->envelope)
        {
            if(area(it.second) == 0)
                continue;

            xl = min(xl, it.second.ll.x);
            xh = max(xh, it.second.ur.x);
            yl = min(yl, it.second.ll.y);
            yh = max(yh, it.second.ur.y);
            ll = min(ll, it.first);
            lh = max(lh, it.first);
        }
    }

    Rect<int> bbox(xl, yl, xh, yh);
    Rect<int> buffArea  = buffer(bbox, _bufferDistance);


    for(int layer=0; layer < num_layers(); layer++)
    {
        grid->intersects(layer, buffArea, _rSpace);
    }
    //cout << boost::format("%s -> rBBox (%d %d) (%d %d) M%d to M%d #Gcells %d\n") % name % xl % yl % xh % yh % ll % lh % _rSpace.size();
}

void HGR::Net::get_routing_space(int _pin1, int _pin2, int _bufferDistance, set<int> &_rSpace)
{
    
    int xl = INT_MAX;
    int yl = INT_MAX;
    int xh = INT_MIN;
    int yh = INT_MIN;
    int ll = num_layers();
    int lh = 0;
    
    Pin* pin1 = get_pin(_pin1);
    Pin* pin2 = get_pin(_pin2);

    for(auto it : pin1->envelope)
    {
        if(area(it.second) == 0)
            continue;

        xl = min(xl, it.second.ll.x);
        xh = max(xh, it.second.ur.x);
        yl = min(yl, it.second.ll.y);
        yh = max(yh, it.second.ur.y);
        ll = min(ll, it.first);
        lh = max(lh, it.first);
    }
    for(auto it : pin2->envelope)
    {
        if(area(it.second) == 0)
            continue;

        xl = min(xl, it.second.ll.x);
        xh = max(xh, it.second.ur.x);
        yl = min(yl, it.second.ll.y);
        yh = max(yh, it.second.ur.y);
        ll = min(ll, it.first);
        lh = max(lh, it.first);
    }


    Rect<int> bbox(xl, yl, xh, yh);
    Rect<int> buffArea  = buffer(bbox, _bufferDistance);


    for(int layer=ll-1; layer <= lh+1; layer++)
    {
        grid->intersects(layer, buffArea, _rSpace);
    }

}


void HGR::Net::guide_gen()
{   

    Topology* tp = get_topology(id);
    int xl, yl, xh, yh, layer;

    for(int i=0; i < (int)tp->segments.size(); i++)
    {
        Segment* s = &tp->segments[i];
        Gcell* c1 = grid->gcell(s->g1);
        Gcell* c2 = grid->gcell(s->g2);

        xl = min(c1->rect.ll.x, c2->rect.ll.x);
        yl = min(c1->rect.ll.y, c2->rect.ll.y);
        xh = max(c1->rect.ur.x, c2->rect.ur.x);
        yh = max(c1->rect.ur.y, c2->rect.ur.y);
        layer = s->layer;

        guides.push_back( { layer, Rect<int>(xl, yl, xh, yh) } );
    }

}   




