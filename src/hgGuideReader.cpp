#include "hgCircuit.h"
#include "hgRouter.h"
#include <boost/tokenizer.hpp>
#include <stdlib.h>

int HGR::Circuit::read_ispd2019_guide(char* input) {

#ifdef DEBUG
    cout << " -- guide read start -- " << endl; 
#endif
    string line = "";
    string delim = " ";

    ifstream inputFile(input);
    bool flag = false;


    while(!inputFile.eof())
    {
        if(!getline(inputFile, line)) 
        {
            //cout << "?" << endl;
            continue;
        }
        //cout << line << endl;

        boost::char_separator<char> sep(delim.c_str());
        boost::tokenizer<boost::char_separator<char>> tokens(line, sep);
        typedef boost::tokenizer<boost::char_separator<char>>::iterator iteratorToken;

        iteratorToken it = tokens.begin();
        Net* curNet;
        if(!flag)
        {
            curNet = &nets[net2id[*it]];
            flag = true;
        }
        else
        {
            if(*it == "(") 
                continue;
            else if(*it == ")")
            {
                flag = false;
                //curNet->print_guide();

                continue;
            }
            else
            {
                int lx = atoi((it++)->c_str());
                int ly = atoi((it++)->c_str());
                int ux = atoi((it++)->c_str());
                int uy = atoi((it++)->c_str());
                int lNum = layer2id[*it];

                curNet->guides.push_back( { lNum, Rect<int>(Point<int>(lx,ly), Point<int>(ux,uy)) } );
            }
        }
    }

    inputFile.close();


#ifdef DEBUG
    cout << " --- guide read end --- " << endl;
#endif

}

void HGR::write_guide()
{
    ckt->write_iccad2019_guide(ckt->outfile);
}


int HGR::Circuit::write_iccad2019_guide(char* output)
{
    ofstream dotOutFile(output);

    if(!dotOutFile.good())
    {
        cerr << "write_guide:: cannot open '" << output << "' for writing. " << endl;
        exit(1);
    }


    for(int i=0; i < num_nets(); i++)
    {
        Net* net = get_net(i);
        net->guide_gen();
        dotOutFile << net->name << endl;
        dotOutFile << "(" << endl;

        for(auto it : net->guides)
        {
            int layer       = it.first;
            Rect<int> rect  = it.second;

            dotOutFile << rect.ll.x << " " << rect.ll.y << " " << rect.ur.x << " " << rect.ur.y << " " << get_metal(layer)->name << endl;
        }

        dotOutFile << ")" << endl;
    }

    dotOutFile.close();
    return 0;
}





void HGR::Net::print_guide()
{
    printf("%s\n(\n", name.c_str());
    for(int i=0; i < guides.size(); i++)
    {
        int lNum = guides[i].first;
        Rect<int> rect = guides[i].second;

        printf("%d %d %d %d %s\n", rect.ll.x, rect.ll.y, rect.ur.x, rect.ur.y, ckt->metals[lNum].name.c_str());

    }
    printf(")\n\n");


}




