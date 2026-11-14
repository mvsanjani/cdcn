
# 1. CHARACTER COUNT

def character_count(frames):
    result = ""

    for f in frames:
        result += str(len(f) + 1) + f

    return result


def decode_count(s):
    frames = []
    i = 0

    while i < len(s):
        n = int(s[i])
        frames.append(s[i+1:i+n])
        i += n

    return frames


# 2. CHARACTER STUFFING

FLAG = "FLAG"
ESC = "ESC"

def character_stuff(data):
    words = data.split()
    result = [FLAG]

    for word in words:
        if word == FLAG or word == ESC:
            result.append(ESC)

        result.append(word)

    result.append(FLAG)

    return " ".join(result)


def character_destuff(frame):
    words = frame.split()[1:-1]
    result = []
    i = 0

    while i < len(words):
        if words[i] == ESC:
            i += 1

        result.append(words[i])
        i += 1

    return " ".join(result)


# 3. BIT STUFFING

def bit_stuff(bits):
    result = ""
    count = 0

    for b in bits:
        result += b

        if b == '1':
            count += 1
        else:
            count = 0

        if count == 5:
            result += '0'
            count = 0

    return "01111110" + result + "01111110"


def bit_destuff(frame):
    data = frame[8:-8]
    result = ""
    count = 0
    i = 0

    while i < len(data):
        result += data[i]

        if data[i] == '1':
            count += 1
        else:
            count = 0

        if count == 5:
            i += 1
            count = 0

        i += 1

    return result


# MAIN PROGRAM

print("1. CHARACTER COUNT")

frames = input("Enter frames separated by space: ").split()
s = character_count(frames)

print("Transmitted stream:", s)
print("Received frames:", decode_count(s))


print("\n2. CHARACTER STUFFING")

data = input("Enter data: ")
f = character_stuff(data)

print("Stuffed frame:", f)
print("After de-stuffing:", character_destuff(f))


print("\n3. BIT STUFFING")

bits = input("Enter bit string: ")
f = bit_stuff(bits)

print("Stuffed frame:", f)
print("After de-stuffing:", bit_destuff(f))
