#include<fstream>
#include"parser.cpp"

int main(int argc,char* argv[]){
    if(argc<2)
    {
        std::cerr << "give atleast 3 parameters\n";
        exit(EXIT_FAILURE);
    }
    std::string source,path=argv[1];
    {
        std::ifstream file(path);
        std::string line;
        while (std::getline(file, line)) 
        {
            source += line + ";";
        }
    }
    bool debugging=(std::string)argv[2]=="debug";
    source.push_back('\0');
    Tokenizer tokenizer(source);
    std::vector<Token> tokens=tokenizer.tokenize();
    Parser parser(tokens);
    std::string cppsourcecode=parser.parse();
    if(debugging)
    {
        debug(tokens);
        std::cout << source << std::endl;
        std::cout << cppsourcecode << std::endl; 
    }

    //Command to compile the C++ code from stdin
    std::string compilecommand = "g++ -x c++ -o output -";

    // Open a pipe to the compiler
    FILE* pipe = popen(compilecommand.c_str(), "w");
    if (!pipe) {
        std::cerr << "Failed to invoke compiler!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Write the C++ code to the compiler's stdin
    fwrite(cppsourcecode.c_str(), 1, cppsourcecode.size(), pipe);

    // Close the pipe and check the result
    int compile_result = pclose(pipe);
    if (compile_result != 0) {
        std::cerr << "Compilation failed with exit code: " << compile_result << std::endl;
        exit(compile_result);
    }

    // Execute the compiled program
    int run_result = std::system("output");
    if (run_result != 0) {
        std::cerr << "Execution failed with exit code: " << run_result << std::endl;
        exit(run_result);
    }
    exit(EXIT_SUCCESS);
}