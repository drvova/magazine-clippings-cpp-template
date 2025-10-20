#include "magazine_clippings.hpp"

bool canCreateNote(const std::string& note, const std::vector<std::string>& articles) {
    std::unordered_map<char, int> chars;

    for (auto& article : articles) {
        for (char c : article) {
            if (!isspace(c)) {
                chars[tolower(c)]++;
            }
        }
    }

    for (char c : note) {
        if (!isspace(c)) {
            if (--chars[tolower(c)] < 0) {
                return false;
            }
        }
    }

    return true;
}