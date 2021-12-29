#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

const int MAX_RESULT_DOCUMENT_COUNT = 5;

class SearchServer {
    struct Document {
        int id;
        int relevance;
    };

public:
    void AddDocument(istream& stream, int document_id) {
        for (const string& word : SplitIntoWordsNoStop(ReadLine(stream), stop_words)) {
            word_to_documents[word].insert(document_id);
        }
    }

    void SetStopWords(istream& stream) {
        stop_words = ParseStopWords(ReadLine(stream));
    }

    set<string> GetStopWords() {
        return stop_words;
    }

    void SetDocumentCount(istream& stream) {
        document_count = ReadLineWithNumber(stream);
    }

    int GetDocumentCount() {
        return document_count;
    }

    void SetQuery(istream& stream) {
        query = ReadLine(stream);
    }

    vector<Document> GetTopDocuments() {
        FindAllDocuments();
        vector<Document> top_matched_documents = matched_documents;
        sort(top_matched_documents.begin(), top_matched_documents.end(), HasDocumentGreaterRelevance);
        if (top_matched_documents.size() > MAX_RESULT_DOCUMENT_COUNT) {
            top_matched_documents.resize(MAX_RESULT_DOCUMENT_COUNT);
        }
        return top_matched_documents;
    }

private:
    vector<Document> matched_documents;
    set<string> stop_words;
    int document_count;
    map<string, set<int>> word_to_documents;
    string query;

    static bool HasDocumentGreaterRelevance(Document& lhs, Document& rhs) {
            return lhs.id < rhs.id;
    }

    string ReadLine(istream& stream) {
        string s;
        getline(stream, s);
        return s;
    }

    int ReadLineWithNumber(istream& stream) {
        int result;
        stream >> result;
        ReadLine(stream);
        return result;
    }

    set<string> ParseStopWords(const string& text) {
        set<string> stop_words;
        for (const string& word : SplitIntoWords(text)) {
            stop_words.insert(word);
        }
        return stop_words;
    }

    vector<string> SplitIntoWords(const string& text) {
        vector<string> words;
        string word;
        for (const char c : text) {
            if (c == ' ') {
                words.push_back(word);
                word = "";
            } else {
                word += c;
            }
        }
        words.push_back(word);

        return words;
    }

    vector<string> SplitIntoWordsNoStop(const string& text, const set<string>& stop_words) {
        vector<string> words;
        for (const string& word : SplitIntoWords(text)) {
            if (stop_words.count(word) == 0) {
                words.push_back(word);
            }
        }
        return words;
    }

    void FindAllDocuments() {
        const vector<string> query_words = SplitIntoWordsNoStop(query, stop_words);
        map<int, int> document_to_relevance;
        for (const string& word : query_words) {
                if (word_to_documents.count(word) == 0) {
                    continue;
                }
                for (const int document_id : word_to_documents.at(word)) {
                    ++document_to_relevance[document_id];
                }
            }
            for (auto [document_id, relevance] : document_to_relevance) {
                matched_documents.push_back({document_id, relevance});
            }
    }
};

SearchServer CreateSearchServer() {
    SearchServer search_server;
    search_server.SetStopWords(cin);
    search_server.SetDocumentCount(cin);
    for (int document_id = 0; document_id < search_server.GetDocumentCount(); ++document_id) {
        search_server.AddDocument(cin, document_id);
    }
    search_server.SetQuery(cin);
    return search_server;
}

int main() {
    SearchServer search_server = CreateSearchServer();

    for (auto document : search_server.GetTopDocuments()) {
        cout << "{ document_id = " << document.id << ", relevance = " << document.relevance << " }" << endl;
    }
}
