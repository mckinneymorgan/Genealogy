// Original author: Morgan McKinney 4/2020

#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
#include <vector>
using namespace std;

const int NUM_PEOPLE_EDGES = 2;
const int NUM_FAMILY_EDGES = 12;
const int MAX_FAMILIES = 99;

// Edge
struct edge {
	int start, end;
}; // edge

// Family Vertex
// (Discussed implementation of families with Kayla Woodward)
struct familyVertex {
	int id;
	edge edges[12];
	// Edge index 0 = husband, 1 = wife, 2-11 = child(ren)
}; // familyVertex

// Person Vertex
// (Discussed implementation of people with Kayla Woodward)
struct personVertex {
	int id;
	edge edges[2];
	// Edge index 0 = parent, 1 = marriage
}; // personVertex

// Create Edge
edge createEdge(int s, int e) {
	edge newEdge;
	newEdge.start = s;
	newEdge.end = e;
	return newEdge;
} // createEdge()

// Person
personVertex person(int personID, int parentID, int marriageID) {
	// Introduce person vertex
	personVertex human;
	human.id = personID;
	// Connect to two family vertices
	if (parentID != 0) { // If parent exists
		human.edges[0] = createEdge(personID, parentID); // By parents
	}
	if (marriageID != 0) { // If marriage exists
		human.edges[1] = createEdge(personID, marriageID); // By marriage
	}
	// Print output
	cout << "Person " << personID << " has parents " << parentID;
	cout << " and is married in family " << marriageID << "." <<  endl;
	return human;
} // person()

// Family
familyVertex family(int familyID, int husbandID, int wifeID, vector<int> children) {
	// Intoduce family vertex
	familyVertex fam;
	fam.id = familyID;
	// Connect to family member vertices
	if (husbandID != 0) { // If husband exists
		fam.edges[0] = createEdge(familyID, husbandID);
	}
	if (wifeID != 0) { // If wife exists
		fam.edges[1] = createEdge(familyID, wifeID);
	}
	for (size_t i = 0; i < children.size(); i++) { // Connect kids, if needed
		fam.edges[i + 2] = createEdge(familyID, children[i]);
	}
	// Print output
	cout << "Family " << familyID << " has husband " << husbandID;
	cout << ", wife " << wifeID << ", and children";
	for (size_t i = 0; i < children.size(); i++) {
		cout << " " <<  children[i];
	}
	cout << "." << endl;
	return fam;
} // family()

// Find Element
int findElement(familyVertex fams[], int element) {
	int index = -1; // Not found by default
	for (int i = 0; i < MAX_FAMILIES; i++) {
		if (fams[i].id == element) {
			index = i;
		}
	}
	return index;
} // findElement()

// Verify
void verify(familyVertex fams[], int famCount, personVertex humans[], int humanCount) {
	bool consistent = true;
	// Loop through every element in people
	for (int i = 0; i < humanCount; i++) {
		// Check if they have relation to a family
		for (int j = 0; j < NUM_PEOPLE_EDGES; j++) {
			// If so, check if they have same relation back
			int familyRelation = humans[i].edges[j].end;

			if (familyRelation != 0) { // Ensure relation is known

			int familyIndex = findElement(fams, familyRelation); // Find family index
			if (familyIndex == -1) { // Matching family not found
				cout << "Person " << i << " doesn't point to ";
				if (j == 0) { // Parent edge
					cout << "parent family " << familyRelation << "." << endl;
				}
				else { // Marriage edge
					cout << "marriage family " << familyRelation << "." << endl;
				}
				consistent = false; // Update consistency
			}
			else { // Matching family found
				// Check for back pointer
				bool backPointer = false; // Not found by default
				for (int k = 0; k < NUM_FAMILY_EDGES; k++) {
					if (fams[familyIndex].edges[k].end == humans[i].id) {
						backPointer = true;
					}
				}
				if (backPointer == false) { // No back-pointer
					cout << "Person " << i << " points to ";
					if (j == 0) { // Parent edge
						cout << "parent family " << familyRelation;
						cout << " but there is no back-pointer." << endl;
					}
					else { // Marriage edge
						cout << "marriage family " << familyRelation;
						cout << " but there is no back-pointer." << endl;
					}
					consistent = false;
				}
			}

			} // End if statement ensuring relation is known
		}
	}
	if (consistent == true) {
		cout << "The data is consistent." << endl;
	}
} // verify()

// BFS
// (Referenced geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph)
void BFS(int start, int vertexCount, familyVertex fams[], personVertex humans[]) {
	bool *visited = new bool[vertexCount];
	for (int i = 0; i < vertexCount; i++) {
		visited[i] = false;
	}
	vector<int> queue;
	visited[start] = true;
	queue.push_back(start);
	while (!queue.empty()) {
		start = queue.back();
		cout << start << " ";
		queue.pop_back();
		// Traverse vertices
		for (auto i = queue.begin(); i != queue.end(); i++) {
			if (!visited[*i]) {
				visited[*i] = true;
				queue.push_back(*i);
			}
		}
	}
}

// Relate
void relate(int personOneID, int personTwoID, familyVertex fams[], int famCount, personVertex humans[], int humanCount) {
	// Relate the people
	int vertexCount = famCount + humanCount;
	BFS(personOneID, vertexCount, fams, humans);
} // relate()

int main() {
	// Initialize family tree
	// (Discussed usage of arrays for families and people with Kayla Woodward)
	familyVertex families[99];
	personVertex people[99];
	int familyCount = 0;
	int personCount = 0;
	for (int i = 0; i < MAX_FAMILIES; i++) { // Initialize members and set to 0
		families[i].id = 0;
		for (int j = 0; j < NUM_FAMILY_EDGES; j++) {
			families[i].edges[j].start = 0;
			families[i].edges[j].end = 0;
		}
		people[i].id = 0;
		for (int j = 0; j < NUM_PEOPLE_EDGES; j++) {
			people[i].edges[j].start = 0;
			people[i].edges[j].start = 0;
		}
	}
	// Read standard input
	string line, word, command;
	while (getline(cin, line)) {
		// Tokenize
		// (Referenced geeksforgeeks.org/tokenizing-a-string-cpp/)
		vector<string> tokens;
		stringstream ss(line);
		while (getline(ss, word, ' ')) {
			tokens.push_back(word);
		}
		// Execute chosen command
		command = tokens[0];
		if (command == "Person") {
			// Person n Parent n Marriage n
			int human = stoi(tokens[1]);
			int parent = stoi(tokens[3]);
			int marriage = stoi(tokens[5]);
			// Create family vertex if needed
			int parentIndex = findElement(families, parent);
			if (parentIndex == -1) { // Parent family not found
				familyVertex fam;
				fam.id = parent;
				families[familyCount] = fam;
				familyCount++;
			}
			int marriageIndex = findElement(families, marriage);
			if (marriageIndex == -1) { // Marriage family not found
				familyVertex fam;
				fam.id = marriage;
				families[familyCount] = fam;
				familyCount++;
			}
			people[personCount] = person(human, parent, marriage);
			personCount++;
		} else {
			if (command == "Family") {
				// Family n Husband n Wife n Child n...
				vector<int> children; // Store children in vector
				for (size_t i = 7; i < tokens.size(); i = i + 2) {
					int j = stoi(tokens[i]);
					children.push_back(j);
				}
				int fam = stoi(tokens[1]);
				int husband = stoi(tokens[3]);
				int wife = stoi(tokens[5]);
				families[familyCount] = family(fam, husband, wife, children);
				familyCount++; // Increment family count
			}
			else {
				if (command == "Relate") {
					// Relate n n
					int person1 = stoi(tokens[1]);
					int person2 = stoi(tokens[2]);
					relate(person1, person2, families, familyCount, people, personCount);
				}
				else {
					// Verify
					verify(families, familyCount, people, personCount);
				}
			}
		}
	}
	return 0;
}
