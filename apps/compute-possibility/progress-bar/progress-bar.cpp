#ifdef __WIN32
#include <windows.h>
#else
#if defined(unix) || defined(__unix__) || defined(__unix)
#include <sys/ioctl.h>
#include <unistd.h>
#endif
#endif
#include "progress-bar.h"

namespace RiskRoll {
ProgressBar::ProgressBar(std::shared_ptr<std::ostream> ptr_outstream,
            std::shared_ptr<struct Details> ptr_details){
    this->ptr_outstream = ptr_outstream;
    this->ptr_details = ptr_details;
    this->t_width = ProgressBar::getConsoleWidth();
}

void ProgressBar::update() {
    // Implicit conversion to float using 100.0 instead of 100
    // No enough: (unsigned int) * (unsigned int) = (unsigned int); (unsigned int) * (float) = (float)
    float percent = static_cast<float>((this->ptr_details)->progress) / static_cast<float>((this->ptr_details)->full) * 100.0;
    std::string prog_bar = '[' + std::string(static_cast<int>(percent / 100 * 50), '#') +
                           std::string(static_cast<int>((100 - percent) / 100 * 50), '-') +
                           ']';
    std::string line = (this->ptr_details)->message + ' ' + prog_bar + ' ' +
                       std::to_string(percent) + "% | " + std::to_string((this->ptr_details)->progress) + '/' +
                       std::to_string((this->ptr_details)->full);
    // When the terminal does not have enough space
    if (line.size() > this->t_width)
        // Replace the last three characters with "..."
        line.replace(line.size() - 3, 3, "...");
    // Add a carriage return to overwrite the last line.
    *(this->ptr_outstream) << '\r' << line;
}

void ProgressBar::update(std::shared_ptr<struct Details> ptr_details) {
    this->ptr_details = ptr_details;
    this->update();
}

void ProgressBar::update(unsigned long long& progress) {
    (this->ptr_details)->progress = progress;
    this->update();
}

void ProgressBar::clear() {
    // Tested; Works on both windows and linux
    *(this->ptr_outstream) << "\x1b[2K";
}

// Platform dependent get console width function.
#ifdef __WIN32
unsigned short ProgressBar::getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwSize.X;
}
#else
#if defined(unix) || defined(__unix__) || defined(__unix)
unsigned short ProgressBar::getConsoleWidth() {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_col;
}
#endif
#endif
}  // namespace RiskRoll
