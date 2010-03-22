
//
// noisebandstk.cpp
//

// /Users/mark/mcgill/research/thesis/researchfiles/phasetwo/garygranular/stk-4.3.0/src/SineWave.cpp
// /Users/mark/mcgill/research/thesis/researchfiles/phasetwo/garygranular/stk-4.3.0/

#include "SineWave.h"
#include "FileWvOut.h"

//using namespace stk; // needed for newer stk

int main( void ) {

    StkFloat lengthseconds = 2;
    unsigned long numsamples = static_cast<unsigned long>(lengthseconds * Stk::sampleRate());
    unsigned long numpartials = 100; // FIXME partials per octave
    StkFloat lofreq = 100;
    StkFloat hifreq = 200;

    // final output
    StkFrames output(0.0, numsamples, 1);

    for ( unsigned long i = 0; i < numpartials; i++ ) {

        std::cout << "adding a sine" << std::endl;

        // FIXME maybe factor this out since the starting phase wouldn't matter anyway
        SineWave thissine;
        thissine.setFrequency( 100 );

        // older stk needs to do this loop manually:
        // newer stk you can just tick on an intermediate buffer and += it into
        // the main output
        for ( unsigned long j = 0; j < numsamples; j++ ) {
            output[j] += thissine.tick();
        }

    }

    std::cout << "done computing" << std::endl;

    std::string outfilename( "outfile.aiff" );

    // write to file
    FileWvOut outfile( outfilename, 1, FileWrite::FILE_AIF, Stk::STK_FLOAT32 );
    outfile.tick( output );
    outfile.closeFile();

    std::cout << "wrote to " << outfilename << std::endl;

};


// vim:sw=4:ts=4:et:ai:ic:
