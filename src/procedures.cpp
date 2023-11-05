// brief: Compute the derivative of a polynomial
proc compute_derivative(list coefficients, int monomial_index)
{
    int n = size(coefficients); // Number of monomials in the list
    list derivatives;

    for (int i = 1; i <= n; i++)
    {
        if (i == monomial_index)
        {
            // Compute the derivative of the monomial with respect to itself
            derivatives[i] = diff(coefficients[i], x(monomial_index));
        }
        else
        {
            // Compute the derivative of the monomial with respect to the given monomial
            derivatives[i] = diff(coefficients[i], x(monomial_index));
        }
    }

    return (derivatives);
}

// brief: Compute the value of the polynomial at the given point
proc substitute_point(list coefficients, list point)
{
    int n = size(coefficients); // Number of coefficients

    list result; // List to store the result

    for (int i = 1; i <= n; i++)
    {
        poly f = coefficients[i];                                                                     // Get the i-th coefficient
        poly subst_result = subst(f, x(0), point[1], x(1), point[2], x(2), point[3], x(3), point[4]); // Substitute the point into the coefficient

        result[i] = subst_result; // Store the substituted coefficient
    }

    return (result);
}

// brief: Create a matrix from a list of elements
proc create_matrix(list elements, int rows, int cols)
{
    matrix mat[rows][cols]; // Create a matrix filled with zeros

    if (rows * cols != size(elements))
    {
        // Check if the number of elements matches the matrix size
        return (mat); // Return an empty matrix
    }

    int element_index = 1; // Index to iterate through the elements list

    for (int i = 1; i <= rows; i++)
    {
        for (int j = 1; j <= cols; j++)
        {
            mat[i, j] = elements[element_index];
            element_index++;
        }
    }

    return (mat);
}

// brief: Extract the coefficients of a polynomial
proc extract_coefficients(poly polynomial)
{
    int num_variables = 4; // Number of variables in the polynomial
    list coefficient_list;

    for (int i = 1; i <= size(polynomial); i++)
    {
        poly f = polynomial[i];

        // You can perform variable substitutions here if needed
        // For example, if you want to substitute all variables b(0), b(1), b(2), and b(3) to 1:
        for (int j = 0; j < num_variables; j++)
        {
            f = subst(f, x(j), 1);
        }

        // Get the coefficient of the polynomial
        coefficient_list = coefficient_list + list(f);
    }

    return (coefficient_list);
}

// brief: Create an ideal from a list of polynomials
proc ideal_from_list(list polynomials)
{
    // Create an ideal from a list of polynomials
    ideal I = ideal(polynomials[1..size(polynomials)]);

    // Compute the Groebner basis of the ideal
    I = std(I);

    return (I);
}

// brief: Compute the Weddle surface
proc compute_weddle_surface(list points)
{
    poly weddle;

    if (6 != size(points))
    {
        // Check if the number of points is 6
        return (weddle); // Return a zero poly
    }

    // List of coefficients of monomials of degree 2 in P^3
    list coefficients =
        list(x(0) ^ 2,
             x(1) ^ 2,
             x(2) ^ 2,
             x(3) ^ 2,
             x(0) * x(1),
             x(0) * x(2),
             x(0) * x(3),
             x(1) * x(2),
             x(1) * x(3),
             x(2) * x(3));

    // Lists of derivatives of monomials of degree 2 in P^3
    list derivatives_x0 = compute_derivative(coefficients, 0);
    list derivatives_x1 = compute_derivative(coefficients, 1);
    list derivatives_x2 = compute_derivative(coefficients, 2);
    list derivatives_x3 = compute_derivative(coefficients, 3);

    // List of elements of the matrix
    list matrixList =
        substitute_point(coefficients, points[1]) +
        substitute_point(coefficients, points[2]) +
        substitute_point(coefficients, points[3]) +
        substitute_point(coefficients, points[4]) +
        substitute_point(coefficients, points[5]) +
        substitute_point(coefficients, points[6]) +
        derivatives_x0 +
        derivatives_x1 +
        derivatives_x2 +
        derivatives_x3;

    // Create a matrix from the list of elements
    matrix M = create_matrix(matrixList, 10, 10);

    // Compute the determinant of the matrix
    poly weddle = det(M);

    return (weddle);
}