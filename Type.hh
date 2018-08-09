#ifndef TYPE_HH
#define TYPE_HH

class Type {
private:
	static std::unordered_map<std::string, int> types;
	static std::vector <std::vector <int> > weaknesses;
	std::string name;

public:
	Type();
	
	/* Pre: TODO */
	/* Post: TODO */
	Type(std::string name);

	/* Pre: TODO */
	/* Post: TODO */
	std::string get_name();
	
	/* Pre: TODO */
	/* Post: TODO */
	static int advantage(Type t1, Type t2);
	
	/* Pre: TODO */
	/* Post: TODO */
	static int advantage(std::string t1, std::string t2);
		
	/* Pre: TODO */
	/* Post: TODO */
	static void initialize();
};

#endif
