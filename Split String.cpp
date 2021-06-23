vector <string> split(string& s, char delimiter) {
	cout << s << endl;
	vector <string> tokens;
	string token;
	istringstream tokenStream(s);
	while (getline(tokenStream, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}