#!/usr/bin/env python3
import random
import string
import argparse

def random_word(min_len=3, max_len=8):
    length = random.randint(min_len, max_len)
    return ''.join(random.choices(string.ascii_lowercase, k=length))

def write_test(filename: str,
               pattern_len: int,
               text_len: int,
               vocabulary_size: int,
               mode: str):
    """
    Генерирует файл input.txt:
    1-я строка — шаблон (pattern_len слов)
    далее — text_len слов, разделённых пробелом (можно разбить на несколько строк)
    mode:
      * 'random' — слова равновероятно из словаря
      * 'worst'  — все слова в тексте одинаковы и не совпадают с последним словом шаблона
      * 'best'   — все слова в тексте одинаковы и совпадают с последним словом шаблона
    """
    vocab = [random_word() for _ in range(vocabulary_size)]
    # собираем шаблон
    pattern = [random.choice(vocab) for _ in range(pattern_len)]
    # текст
    text = []
    if mode == 'random':
        for _ in range(text_len):
            text.append(random.choice(vocab))
    elif mode == 'worst':
        # пусть в шаблоне последнее слово = 'X', а в тексте все «Y» != X
        last = pattern[-1]
        others = [w for w in vocab if w != last]
        fill = others[0] if others else last + "z"
        text = [fill] * text_len
    elif mode == 'best':
        # совпадает с последним словом шаблона → каждый сдвиг на pattern_len
        fill = pattern[-1]
        text = [fill] * text_len
    else:
        raise ValueError("unknown mode")

    # пишем в файл
    with open(filename, 'w', encoding='utf-8') as f:
        f.write(' '.join(pattern) + '\n')
        # разобьём текст по 100 слов на строку
        for i in range(0, text_len, 100):
            f.write(' '.join(text[i:i+100]) + '\n')

if __name__ == '__main__':
    p = argparse.ArgumentParser(description="Генератор тестов для naive vs BM")
    p.add_argument('--pattern-len', type=int, default=50,
                   help="длина шаблона в словах")
    p.add_argument('--text-len',    type=int, default=1000000,
                   help="длина текста в словах")
    p.add_argument('--vocab-size',  type=int, default=100,
                   help="размер словаря")
    p.add_argument('--mode', choices=['random','worst','best'], default='random',
                   help="тип теста")
    p.add_argument('--output', type=str, default='input.txt',
                   help="имя файла для генерации")
    args = p.parse_args()

    write_test(
        filename=args.output,
        pattern_len=args.pattern_len,
        text_len=args.text_len,
        vocabulary_size=args.vocab_size,
        mode=args.mode
    )
    print(f"Тест записан в «{args.output}» (mode={args.mode})")
