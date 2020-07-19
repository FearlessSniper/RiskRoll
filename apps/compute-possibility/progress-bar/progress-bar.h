#include <iostream>
#include <memory>
#include <string>

namespace RiskRoll {
/*
A progress bar made of simple characters.
Like:
    Computing... [##########----------------------------------------] 10% | n/n
*/
class ProgressBar {
   public:
    struct Details {
        std::string message;
        // Use unsigned long long so that its larger
        unsigned long long progress;
        unsigned long long full;
    };
    // Create a progress bar with output stream;
    // t_width: terminal width
    ProgressBar(std::ostream* ptr_outstream,
                std::shared_ptr<struct Details> details);
    // As the Details structure is passed by a pointer,
    // updating the structure passed would be known by the
    // class. So simply call this one.
    void update();
    // Do not use this unless you created another set of Details.
    void update(std::shared_ptr<struct Details> ptr_details);
    // Or only the progress number
    void update(unsigned long long& progress);
    // Clears the progress bar
    void clear();
    // Get the width of the console (implementation is platform dependent)
    static unsigned short getConsoleWidth();

   private:
    std::ostream* ptr_outstream;
    std::shared_ptr<struct Details> ptr_details;
    unsigned int t_width;
};

}  // namespace RiskRoll
