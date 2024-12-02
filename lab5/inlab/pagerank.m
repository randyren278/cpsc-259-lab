% Define the connectivity matrix 
ConnectivityMatrix = [0 1 1 1 1;
     1 0 0 1 0;
     0 0 0 0 0;
     1 1 1 0 0;
     0 1 0 1 0];

% Get the size of the connectivity matrix
[rows, columns] = size(ConnectivityMatrix);

% Get the dimension of the square matrix
dimension = size(ConnectivityMatrix, 1);

% Calculate the sum of each column
columnsums = sum(ConnectivityMatrix, 1);

% Set the random walk probability factor
p = 0.85;

% Find non-zero columns
zerocolumns = find(columnsums ~= 0);

% Create a sparse diagonal matrix
D = sparse(zerocolumns, zerocolumns, 1 ./ columnsums(zerocolumns), dimension, dimension);

% Construct a partial stochastic matrix
StochasticMatrix = ConnectivityMatrix * D;

% Find zero columns
[row, column] = find(columnsums == 0);

% Complete the stochastic matrix
StochasticMatrix(:, column) = 1 / dimension;

% Create the transition matrix
Q = ones(dimension, dimension);
TransitionMatrix = p * StochasticMatrix + (1 - p) * (Q / dimension);

% Initialize the rank vector
PageRank = ones(dimension, 1);

% Iterate to find the PageRank
for i = 1:100
    PageRank = TransitionMatrix * PageRank;
end

% Normalize the rank vector
PageRank = PageRank / sum(PageRank);

% Display the PageRank results
disp('PageRank of each node:');
disp(PageRank);

