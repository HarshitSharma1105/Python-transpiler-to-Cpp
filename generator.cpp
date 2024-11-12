#include"parser.cpp "
#include<sstream>
#include<unordered_set>
class Generator{
public:
    Generator(NodeProg nodeprog):nodeprog(nodeprog){}
    std::string generate(){
        open();
        for(const NodeStmt* nodestmt:nodeprog.NodeStmts){
            if(nodestmt->type==TypeNodeStmt::Print)generate_print(nodestmt);
            else if(nodestmt->type==TypeNodeStmt::Int || nodestmt->type==TypeNodeStmt::Float)generate_assign_float(nodestmt);
            else if(nodestmt->type==TypeNodeStmt::String)generate_assign_string(nodestmt);
        }
        close();
        return stream.str();
    }
private:
    void generate_print(const NodeStmt* nodestmt){
        Token token =nodestmt->var->Print->Print;
        if(token.type==Tokentype::string_lit){
            stream << "    cout << \"" << token.val << "\" << endl;\n";
        }
        else{
            stream << "    cout << " << token.val << " << endl;\n";
        }
    }
    void generate_assign_string(const NodeStmt* nodestmt){
        stream << "    string " << nodestmt->var->String->String.val << ";\n";
    }
    void generate_assign_float(const NodeStmt* nodestmt){
        stream << "    int " << nodestmt->var->String->String.val <<";\n";
    }
    void open(){
        stream << "#include<iostream>\n";
        stream << "using namespace std;\n";
        stream << "int main(){\n";
    }
    void close(){
        stream << "    return 0;\n";
        stream << "}";
    }
private:
    std::unordered_set<std::string> floatmap;
    std::unordered_set<std::string> stringmap;
    NodeProg nodeprog;
    std::stringstream stream;
    int index=0;
};