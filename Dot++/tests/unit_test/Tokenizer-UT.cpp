#include "./platform/UnitTestSupport.hpp"

#include <Dot++/Tokenizer.hpp>
#include <deque>
#include <sstream>

namespace {
    
    struct TokenizerFixture
    {
        TokenizerFixture()
            : tokenizer("test.dot")
        {
        }
        
        dot_pp::Tokenizer tokenizer;
        std::deque<dot_pp::TokenInfo> tokens;
    };
    
    TEST_FIXTURE(TokenizerFixture, verifyInstantation)
    {
    }
    
    TEST_FIXTURE(TokenizerFixture, verifyTokenizationOfWhitespace)
    {
        std::stringstream ss;
        ss << "    \t \n\r\t   \t";
        
        for(const auto c : ss.str())
        {
            tokenizer.consume(c, tokens);
        }
        
        REQUIRE CHECK_EQUAL(0U, tokens.size());
    }
    
    TEST_FIXTURE(TokenizerFixture, verifyTokenizeGraph)
    {
        std::stringstream ss;
        ss  << "digraph test {" "\n"
            << "\t" "a -> b;" "\n"
            << "\t" "a -> c;" "\n"
            << "}\n";
        
        for(const auto c : ss.str())
        {
            tokenizer.consume(c, tokens);
        }
        
        REQUIRE CHECK_EQUAL(12U, tokens.size());
        
        CHECK_EQUAL("digraph", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::keyword, tokens[0].token().type());
        
        CHECK_EQUAL("test", tokens[1].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[1].token().type());
        
        CHECK_EQUAL("{", tokens[2].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::l_paren, tokens[2].token().type());
        
        CHECK_EQUAL("a", tokens[3].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[3].token().type());
        
        CHECK_EQUAL("->", tokens[4].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::directed_edge, tokens[4].token().type());

        CHECK_EQUAL("b", tokens[5].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[5].token().type());
        
        CHECK_EQUAL(";", tokens[6].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::end_statement, tokens[6].token().type());
        
        CHECK_EQUAL("a", tokens[7].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[7].token().type());
        
        CHECK_EQUAL("->", tokens[8].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::directed_edge, tokens[8].token().type());

        CHECK_EQUAL("c", tokens[9].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[9].token().type());

        CHECK_EQUAL(";", tokens[10].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::end_statement, tokens[10].token().type());

        CHECK_EQUAL("}", tokens[11].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::r_paren, tokens[11].token().type());
    }

    TEST_FIXTURE(TokenizerFixture, verifyTokenizeGraphWithGraphAttributes)
    {
        std::stringstream ss;
        ss  << "digraph test {" "\n"
        
            << "\t" "size=\"1,1\";" "\n"
        
            << "\t" "a -> b;" "\n"
            << "\t" "a -> c;" "\n"
            << "}\n";
        
        for(const auto c : ss.str())
        {
            tokenizer.consume(c, tokens);
        }
        
        REQUIRE CHECK_EQUAL(16U, tokens.size());
        
        CHECK_EQUAL("digraph", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::keyword, tokens[0].token().type());
        
        CHECK_EQUAL("test", tokens[1].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[1].token().type());
        
        CHECK_EQUAL("{", tokens[2].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::l_paren, tokens[2].token().type());
        
        CHECK_EQUAL("size", tokens[3].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[3].token().type());

        CHECK_EQUAL("=", tokens[4].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::equal, tokens[4].token().type());
        
        CHECK_EQUAL("1,1", tokens[5].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string_literal, tokens[5].token().type());
        
        CHECK_EQUAL(";", tokens[6].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::end_statement, tokens[6].token().type());
        
        CHECK_EQUAL("a", tokens[7].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[7].token().type());
        
        CHECK_EQUAL("->", tokens[8].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::directed_edge, tokens[8].token().type());

        CHECK_EQUAL("b", tokens[9].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[9].token().type());
        
        CHECK_EQUAL(";", tokens[10].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::end_statement, tokens[10].token().type());
        
        CHECK_EQUAL("a", tokens[11].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[11].token().type());
        
        CHECK_EQUAL("->", tokens[12].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::directed_edge, tokens[12].token().type());

        CHECK_EQUAL("c", tokens[13].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[13].token().type());

        CHECK_EQUAL(";", tokens[14].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::end_statement, tokens[14].token().type());

        CHECK_EQUAL("}", tokens[15].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::r_paren, tokens[15].token().type());
    }

    TEST_FIXTURE(TokenizerFixture, verifyTokenizeGraphWithEdgeAttributes)
    {
        std::stringstream ss;
        ss  << "digraph test {" "\n"
            << "\t" "a -> b -> c -> d;" "\n"
            << "\t" "a -> c [label=arc attr=\"g'\"];" "\n"
            << "}\n";
        
        for(const auto c : ss.str())
        {
            tokenizer.consume(c, tokens);
        }
        
        REQUIRE CHECK_EQUAL(24U, tokens.size());
        
        CHECK_EQUAL("digraph", tokens[0].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::keyword, tokens[0].token().type());
        
        CHECK_EQUAL("test", tokens[1].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[1].token().type());
        
        CHECK_EQUAL("{", tokens[2].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::l_paren, tokens[2].token().type());
        
        CHECK_EQUAL("a", tokens[3].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[3].token().type());
        
        CHECK_EQUAL("->", tokens[4].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::directed_edge, tokens[4].token().type());

        CHECK_EQUAL("b", tokens[5].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[5].token().type());

        CHECK_EQUAL("->", tokens[6].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::directed_edge, tokens[6].token().type());

        CHECK_EQUAL("c", tokens[7].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[7].token().type());

        CHECK_EQUAL("->", tokens[8].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::directed_edge, tokens[8].token().type());
        
        CHECK_EQUAL("d", tokens[9].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[9].token().type());

        CHECK_EQUAL(";", tokens[10].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::end_statement, tokens[10].token().type());
        
        CHECK_EQUAL("a", tokens[11].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[11].token().type());
        
        CHECK_EQUAL("->", tokens[12].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::directed_edge, tokens[12].token().type());

        CHECK_EQUAL("c", tokens[13].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[13].token().type());

        CHECK_EQUAL("[", tokens[14].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::l_bracket, tokens[14].token().type());

        CHECK_EQUAL("label", tokens[15].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[15].token().type());

        CHECK_EQUAL("=", tokens[16].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::equal, tokens[16].token().type());

        CHECK_EQUAL("arc", tokens[17].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[17].token().type());

        CHECK_EQUAL("attr", tokens[18].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string, tokens[18].token().type());

        CHECK_EQUAL("=", tokens[19].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::equal, tokens[19].token().type());

        CHECK_EQUAL("g'", tokens[20].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::string_literal, tokens[20].token().type());

        CHECK_EQUAL("]", tokens[21].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::r_bracket, tokens[21].token().type());

        CHECK_EQUAL(";", tokens[22].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::end_statement, tokens[22].token().type());

        CHECK_EQUAL("}", tokens[23].token().to_string());
        CHECK_EQUAL(dot_pp::TokenType::r_paren, tokens[23].token().type());
    }
}
