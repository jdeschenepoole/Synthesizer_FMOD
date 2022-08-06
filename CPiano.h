
#include <vector>

class CPiano
{
public:
	CPiano();
	~CPiano();

	float getNotesFromKeys(int key);


private:
	std::vector<float> notes;
	void createNotes();
};