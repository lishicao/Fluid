#ifndef SPACE_HH_INCLUDED
#define SPACE_HH_INCLUDED

#include <vector>

class space
{
	public :
		vector < particle > particles ;
		vector < mesh > objects ;
	private :
		bool  stopflag ;
	public :
		void  run() ;
		void  stop() ;
}

#endif
