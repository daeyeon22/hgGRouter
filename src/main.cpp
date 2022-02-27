#include "hgCircuit.h"
#include "mymeasure.h"
#include "hgRouter.h"

//#include "func.h"
//#include "util.h"

using namespace std;
using namespace HGR;

static CMeasure measure;

int main(int argc, char** argv)
{
	//char *lef = NULL, *def = NULL, *guide = NULL, *threads = NULL, *outfile = NULL;

    ckt->lef = NULL;
    ckt->def = NULL;
    ckt->guide = NULL;
    ckt->outfile = NULL;
    ckt->threads = NULL;


	cout << "===================================================================" <<endl;
	cout << "    ICCAD 2019 Contest on LEF/DEF Based Open-Source Global Router  " <<endl;
    cout << "    Team Number :  00                                              " <<endl;
	cout << "    Members     :  Daeyeon Kim, Sung-Yun Lee                       " <<endl;
	cout << "    Advisor     :  Seokhyeong Kang                                 " <<endl;
    cout << "    Affiliation :  Pohang University of Science and Technology     " <<endl;
	cout << "===================================================================" <<endl;
    
	measure.start_clock();
    int tat;
	for (int i=1; i < argc; i++) {
		if(i+1 != argc) {
			if( strncmp(argv[i], "-lef", 4) == 0 )
				ckt->lef = argv[++i];
			else if (strncmp(argv[i], "-def", 4) == 0 )
				ckt->def = argv[++i];
			//else if (strncmp(argv[i], "-guide", 6) == 0 )
			//	ckt->guide = argv[++i];
            else if (strncmp(argv[i], "-output", 7) == 0 )
				ckt->outfile = argv[++i];
			else if (strncmp(argv[i], "-threads", 8) == 0 )
				ckt->threads = argv[++i];
            //else if (strncmp(argv[i], "-tat", 4) == 0 )
            //    tat = atoi(argv[++i]);
		}
	}
	
    if( ckt->lef == NULL || ckt->def == NULL ) {
		cerr << "Input files are missing. Check again lef, def and guide files" << endl;
		exit(0);
	}

    string lef_str = ckt->lef;
    size_t found = lef_str.find_last_of("/\\");
    string dir_bench = lef_str.substr(0,found);
    string benchName = dir_bench.substr(dir_bench.find_last_of("/\\")+1);
    ckt->benchName = dir_bench.substr(dir_bench.find_last_of("/\\")+1);
    //benchName.c_str();

	//circuit ckt;
    /* Parsing Here */
    cout << "[Args] Bench name : " << ckt->benchName    << endl; 
    cout << "[Args] lef        : " << ckt->lef          << endl;
    cout << "[Args] def        : " << ckt->def          << endl;
    cout << "[Args] out        : " << ckt->outfile      << endl;

    /* Parsing Here */
    parsing();
    measure.stop_clock("Parsing");
    
    init();
    measure.stop_clock("Initialize");

    pin_extension();
    measure.stop_clock("Pin Extensione");

    route_all();
    measure.stop_clock("Route All");

    write_guide();
    measure.stop_clock("Write Guide");

    measure.print_clock();
	measure.printMemoryUsage();
    cout << " - - - - < program done > - - - - " << endl;
	return 0;

}

// Global Variable
HGR::Grid3D*     HGR::Grid3D::instance    = nullptr;
HGR::Rtree*      HGR::Rtree::instance     = nullptr;
HGR::DRC*        HGR::DRC::instance       = nullptr;
HGR::Circuit*    HGR::Circuit::instance   = nullptr;
HGR::Router*     HGR::Router::instance    = nullptr;


// Singleton Caller
HGR::Grid3D* HGR::Grid3D::inst()
{
    if(instance == nullptr)
        instance = new Grid3D();
    return instance;
}

HGR::Rtree* HGR::Rtree::inst()
{
    if(instance == nullptr)
        instance = new Rtree();
    return instance;
}

HGR::Circuit* HGR::Circuit::inst()
{
    if(instance == nullptr)
        instance = new Circuit();
    return instance;
}

HGR::DRC* HGR::DRC::inst()
{
    if(instance == nullptr)
        instance = new DRC();
    return instance;
}

HGR::Router* HGR::Router::inst()
{
    if(instance == nullptr)
        instance = new Router();
    return instance;
}




