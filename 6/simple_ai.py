import random

class Game:
    def __init__(self, num_range):
        self.num_range = num_range
        self.reset()

    def computer_turn(self):
        if self.last_comp_turn is None:
            self.last_comp_turn = random.randint(-self.num_range, self.num_range)
        return self.last_comp_turn

    def get_loss(self, num):
        return abs(num + self.last_comp_turn)

    def reset(self):
        self.last_comp_turn = None

class SimpleMultiplier:
    def __init__(self, min_mult, max_mult):
        assert min_mult <= max_mult
        self.min_mult = min_mult
        self.max_mult = max_mult
        self.curr_mult = random.uniform(min_mult, max_mult)

    def predict(self, x):
        return self.curr_mult * x

    def evolve(self, x, y, loss):
        # TODO
        pass

class Ai:
    def __init__(self, game, strategy):
        self.game = game
        self.strategy = strategy

    def single_play(self):
        # get the computer's turn
        computer_turn = self.game.computer_turn()

        # get the AI's turn
        ai_turn = self.strategy.predict(computer_turn)

        # figure out how good the AI did
        loss = game.get_loss(ai_turn)

        # reset the game
        self.game.reset()

        return computer_turn, ai_turn, loss

    def benchmark(self, rounds):
        return sum(self.single_play()[2] for i in range(rounds)) / rounds

    def train(self, num_rounds):
        # calculate the average loss before training
        before_loss = self.benchmark(num_rounds)

        # evolving the AI
        for i in range(num_rounds):
            computer_turn, ai_turn, loss = self.single_play()
            self.strategy.evolve(computer_turn, ai_turn, loss)

        # calculate the average loss after training
        after_loss = self.benchmark(num_rounds)

        return before_loss, after_loss


if __name__ == '__main__':
    game = Game(100)
    strategy = SimpleMultiplier(-1, 1)
    ai = Ai(game, strategy)

    before, after = ai.train(1000)
    print("Loss before train: {}\nLoss after train: {}".format(before, after))
