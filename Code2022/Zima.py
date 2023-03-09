def citanje_ulaza():
    try:
        file = open('00-example.txt', 'r')

        lines = file.readlines()
        Pandora = [int(i) for i in lines[0].split(' ')]
        demons = []
        for demon in range(1, Pandora[3] + 1):
            demons.append([int(i) for i in lines[demon].split(' ')])

        file.close()
        return Pandora, demons
    except FileNotFoundError:
        print("Nema fajla")
        return None, None
