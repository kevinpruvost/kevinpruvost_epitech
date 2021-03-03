#
#   Pattern Tree
#

class PatternBranch:
    def __init__(self, patterns = None, depth = 7):
        depth = depth - 1
        if depth < 0:
            self.array = []
        else:
            self.array = [PatternBranch(None, depth), PatternBranch(None, depth), PatternBranch(None, depth)]
        self.score = 0
        if patterns is not None:
            self.initPatterns(patterns)

    def initPatterns(self, patterns):
        for pattern in patterns:
            if len(pattern['vals']) == 2:
                self.array[pattern['vals'][0]][pattern['vals'][1]].score = pattern['score']
            elif len(pattern['vals']) == 3:
                self.array[pattern['vals'][0]][pattern['vals'][1]][pattern['vals'][2]].score = pattern['score']
            elif len(pattern['vals']) == 4:
                self.array[pattern['vals'][0]][pattern['vals'][1]][pattern['vals'][2]][pattern['vals'][3]].score = pattern['score']
            elif len(pattern['vals']) == 5:
                self.array[pattern['vals'][0]][pattern['vals'][1]][pattern['vals'][2]][pattern['vals'][3]][pattern['vals'][4]].score = pattern['score']
            elif len(pattern['vals']) == 6:
                self.array[pattern['vals'][0]][pattern['vals'][1]][pattern['vals'][2]][pattern['vals'][3]][pattern['vals'][4]][pattern['vals'][5]].score = pattern['score']
            elif len(pattern['vals']) == 7:
                self.array[pattern['vals'][0]][pattern['vals'][1]][pattern['vals'][2]][pattern['vals'][3]][pattern['vals'][4]][pattern['vals'][5]][pattern['vals'][6]].score = pattern['score']

    def __getitem__(self, key):
        try:
            return self.array[key]
        except:
            raise RuntimeError("Index out of bounds")

    def __setitem__(self, key, value):
        try:
            self.array[key].score = value
        except:
            raise RuntimeError("Index out of bounds")