def main():
    text = input("Enter Text: ")

    letters = countLetters(text)
    words = countWords(text)
    sentences = countSentences(text)

    gradeLevel = round(0.0588 * (( letters / words) * 100.0) - 0.296 * ((sentences / words) * 100.0) - 15.8)

    if gradeLevel >= 16:
        print("Grade 16+")
    elif gradeLevel < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {gradeLevel}")

def countLetters(text):
    textLength = len(text)
    count = 0

    for textIndex in range(textLength):

        if text[textIndex].isalpha():
            count += 1

    return count

def countWords(text):
    textLength = len(text)
    count = 0

    for textIndex in range(textLength):
        characterIsSpace = text[textIndex] == ' '

        if characterIsSpace:
            count += 1
    
    return count + 1

def countSentences(text):
    textLength = len(text)
    count = 0

    for textIndex in range(textLength):
        characterIsExclamationMark = text[textIndex] == '!'
        characterIsQuestionMark = text[textIndex] == '?'
        characterIsPeriod = text[textIndex] == '.'

        if characterIsExclamationMark or characterIsQuestionMark or characterIsPeriod:
            count += 1

    return count

main()