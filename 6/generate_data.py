import numpy as np
import pandas


def make_regression_data(num_samples, num_features, regression_func, noise=0.1):
    X = np.random.random((num_samples, num_features))
    y = np.apply_along_axis(regression_func, 1, X).reshape(-1, 1)
    y += noise * (np.random.random(y.shape) - 0.5)

    data = np.concatenate((X, y), axis=1)
    column_names = [f'feature{i}' for i in range(num_features)] + ['result']

    df = pandas.DataFrame(data, columns=column_names)
    print(df)

    df.to_csv('regression_data.csv', index=False)

def make_classification_data(num_samples, num_features, classification_func,
                             num_classes, noise=0.1):
    X = np.random.random((num_samples, num_features))
    y = np.apply_along_axis(classification_func, 1, X).reshape(-1, 1)
    X += noise * (np.random.random(X.shape) - 0.5)

    data = np.concatenate((X, y), axis=1)
    column_names = [f'feature{i}' for i in range(num_features)] + ['result']

    df = pandas.DataFrame(data, columns=column_names)
    print(df)

    df.to_csv('classification_data.csv', index=False)


def regression_func(x):
    return x[0] + x[1] + 2

def classification_func(x):
    return int(x[0] < x[1] ** 2)

if __name__ == '__main__':
    # make_regression_data(100, 2, regression_func, noise=0.1)
    make_classification_data(500, 2, classification_func, 2, noise=0.1)

