#include"tokenizer.cpp"

struct NodeInt{
    Token Int;
    Token ident;
};
struct NodeFloat{
    Token Float;
    Token ident;
};
struct NodeString{
    Token String;
    Token ident;
};
struct NodePrint{
    Token Print;
    Token ident;
};
union UnionNodeStmt{
    NodeInt* Int;
    NodeFloat* Float;
    NodeString* String;
    NodePrint* Print;
};

enum TypeNodeStmt{
    Int,
    Float,
    String,
    Print
};

struct NodeStmt{
    UnionNodeStmt* var;
    TypeNodeStmt type;
};

struct NodeProg{
    std::vector<NodeStmt*> NodeStmts;
};

class Parser{
public:
    Parser(const std::vector<Token>& tokens): tokens(tokens){}
    NodeProg parse(){
        NodeProg prog;
        while(peek().type!=Tokentype::dontread){
            if(peek().type==Tokentype::print){
                NodeStmt* nodestmt=new NodeStmt();
                nodestmt->var=new UnionNodeStmt();
                nodestmt->var->Print=new NodePrint();
                consume();
                try_consume(Tokentype::open_paren,"expected '('");
                if(peek().type==Tokentype::open_double){
                    consume();
                    nodestmt->var->Print->Print=consume();
                    try_consume(Tokentype::closed_double,"expected '\"");

                }
                else {
                    nodestmt->var->Print->Print=consume();
                }
                nodestmt->type=TypeNodeStmt::Print;
                prog.NodeStmts.push_back(nodestmt);
                try_consume(Tokentype::closed_paren," expected ')");
            } 
            else if(peek().type==Tokentype::identifier){
                std::string buffer="";
                buffer+=consume().val;
                if(peek().type==Tokentype::assignment){
                    buffer+=consume().val;
                    NodeStmt* nodestmt=new NodeStmt();
                    nodestmt->var=new UnionNodeStmt();
                    if(peek().type==Tokentype::integer_lit){
                        nodestmt->var->Int=new NodeInt();
                        buffer+=consume().val;
                        nodestmt->var->Int->Int.val=buffer;
                        buffer.clear();
                        nodestmt->type=TypeNodeStmt::Int;
                    }
                    else if(peek().type==Tokentype::open_double){
                        nodestmt->var->String=new NodeString();
                        buffer+=consume().val;
                        buffer+=consume().val;
                        buffer+=try_consume(Tokentype::closed_double,"expected \"").val;
                        nodestmt->var->String->String.val=buffer;
                        nodestmt->type=TypeNodeStmt::String;
                        buffer.clear();
                    }
                    else{
                        std::cerr << "Not implemented yet\n";
                        exit(EXIT_FAILURE);
                    }
                    prog.NodeStmts.push_back(nodestmt);
                }
            }  
        }
        return prog;
    }   
private:
    Token peek(int offset=0){
        if(index+offset>=tokens.size()){
            return {Tokentype::dontread,""};
        }
        return tokens[index+offset];
    }
    Token consume(){
        return tokens[index++];
    }
     Token try_consume(const Tokentype& type, const std::string& err_msg)
    {
        if (peek().type == type) {
            return consume();
        }
        std::cerr << err_msg << std::endl;
        exit(EXIT_FAILURE);
    }

    Token try_consume(const Tokentype& type)
    {
        if (peek().type == type) {
            return consume();
        }
        return {Tokentype::dontread,""};
    }
    std::vector<Token> tokens;
    int index=0;
};