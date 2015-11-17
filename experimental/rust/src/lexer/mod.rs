pub mod token;
pub mod tokenizer;
pub mod symboltree;
pub mod symbolreader;
pub mod stringreader;
pub mod typereader;

#[cfg(test)]
mod tests;

pub use self::token::*;
pub use self::symboltree::TokenDef;
pub use self::symboltree::generate_tree;
pub use self::symboltree::Node;
pub use self::typereader::TypeReader;

use std::vec::Vec;

pub struct Lexer;

impl Lexer {

    pub fn new() -> Lexer {
        return Lexer;
    }

    pub fn read(&self, input: &String) -> Vec<Token> {
        let mut tokens = Vec::new();
        let mut tokenizer: Option<Box<tokenizer::Tokenizer>> = None;
        let mut line_num = 1;
        for c in input.chars() {
            let mut to_set: Option<Box<tokenizer::Tokenizer>> = None;
            let mut clear = true;

            if c == '\n' {
                line_num += 1;
            }

            if let &mut Some(ref mut t) = &mut tokenizer {
                if !t.read(c, line_num) {
                    if let Some(tok) = t.publish() {
                        tokens.push(Token{
                            typ: tok,
                            line_num: line_num
                        });
                    }
                } else {
                    clear = false;
                }
            }

            if clear {
                let mut new_tokenizer: Box<tokenizer::Tokenizer> = match c {
                    '0'...'9' => Box::new(tokenizer::NumReader::new()),
                    'a'...'z' => Box::new(stringreader::StringReader::new()),
                    'A'...'Z' => Box::new(typereader::TypeReader::new()),
                    _ => Box::new(symbolreader::SymbolReader::new()),
                };
                new_tokenizer.read(c, line_num);
                tokenizer = Some(new_tokenizer);
            }
        }

        if let &mut Some(ref mut t) = &mut tokenizer {
            if let Some(tok) = t.publish() {
                tokens.push(Token{ typ: tok, line_num: line_num});
            }
        }

        return tokens;
    }
}
