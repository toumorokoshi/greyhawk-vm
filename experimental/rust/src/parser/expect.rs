use lexer::token::TokenType;
use super::Parser;

pub type ExpectResult<T> = Result<T, String>;

pub fn typ(parser: &mut Parser) -> ExpectResult<String> {
    match try_option!(parser.peek(), "type check".to_string()).typ {
        TokenType::Type(ref t) => Ok(t.clone()),
        _ => Err("expected a type.".to_string())
    }
}

pub fn symbol(parser: &mut Parser) -> ExpectResult<String> {
    match try_option!(parser.peek(), "looking for symbol".to_string()).typ {
        TokenType::Type(ref t) => Ok(t.clone()),
        _ => Err("expected a symbol.".to_string())
    }
}

pub fn expect<'a>(parser: &mut Parser, t: TokenType) -> ExpectResult<()> {
    let next = try_option!(parser.next(), "expected a token".to_string());
    if next.typ == t {
        Ok(())
    } else {
        Err(format!("expected a token of {}, found {}", t, next.typ))
    }
}
