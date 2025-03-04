#include <iostream>

#include "gst.cpp"

using namesapce std;

int main() {
    auto start = std::chrono::system_clock::now();  // Start counting running time

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
        std::cout << "Running time:\t" << to_string_with_precision(elapsed_time_minutes, 3) << " minutes\n\n";
    }
}