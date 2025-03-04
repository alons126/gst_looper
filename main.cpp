/*
/cvmfs/oasis.opensciencegrid.org/mis/apptainer/current/bin/apptainer shell --shell=/bin/bash -B /cvmfs,/exp,/nashome,/pnfs/genie,/opt,/run/user,/etc/hostname,/etc/hosts,/etc/krb5.conf --ipc --pid /cvmfs/singularity.opensciencegrid.org/fermilab/fnal-dev-sl7:latest

cd $MY_USER_FOLDER/GENIE

source genie_env.sh

source /cvmfs/fermilab.opensciencegrid.org/products/common/etc/setup
setup fife_utils

cd /pnfs/genie/scratch/users/asportes/gst_looper

source run.sh
 */

#include <iostream>

#include "gst.cpp"
#include "source/namespaces/utilities/utilities.cpp"

using namespace std;
using namespace utilities;

int main() {
    auto start = std::chrono::system_clock::now();  // Start counting running time

    system("rm ./*.pdf");

    string BaseDir = "/pnfs/genie/persistent/users/asportes/2N_Analysis_Samples";

    string Target = "C12";

    string GENIE_tune = "G18_10a_00_000";

    string BeamE = "2070MeV";

    string Q2_th = "Q2_0_02";

    string filesPath = BaseDir + "/" + Target + "/" + GENIE_tune + "/" + BeamE + "_" + Q2_th + "/master-routine_validation_01-eScattering/" + Target + "_" + GENIE_tune + "_" + Q2_th + "_" +
                       BeamE + ".root";

    const char *files = filesPath.c_str();
    // const char *files = "*.root";

    gst loopTree = gst(files);

    loopTree.Loop();

    auto end = std::chrono::system_clock::now();
    auto elapsed_time_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    double elapsed_time_minutes = elapsed_time_seconds.count() / 60;

    if (elapsed_time_seconds.count() < 60) {
        std::cout << "Running time:\t" << elapsed_time_seconds.count() << " seconds\n\n";
    } else {
        std::cout << "Running time:\t" << ToStringWithPrecision(elapsed_time_minutes, 3) << " minutes\n\n";
    }
}