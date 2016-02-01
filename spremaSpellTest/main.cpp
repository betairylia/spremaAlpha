#include <iostream>
#include "spellAnalyser.h"

using namespace std;

int main()
{
	spellAnalyser analyser;
	cout << analyser.readSpellFromFile("testSpell-dircFlameArray.txt") << endl << endl;
	analyser.doSpell(analyser.readSpellFromFile("testSpell-dircFlameArray.txt"));

	cout << "Type in anything then press Enter..." << endl;
	char c;
	cin >> c;

	return 0;
}