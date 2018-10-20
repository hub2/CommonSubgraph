package graph

import "errors"

type Builder struct {
	adjMatrix [][]int
}

func New(v int) (*Builder, error) {
	if v < 1 {
		return nil, errors.New("at least 1 vertex needed")
	}

	matrix := make([][]int, v)
	for i := range matrix {
		matrix[i] = make([]int, v)
	}
	return &Builder{matrix}, nil
}

func (b *Builder) AddEdge(from, to int) error {
	if !b.vertexIndexValid(from) {
		return errors.New("from vertex invalid")
	}
	if !b.vertexIndexValid(to) {
		return errors.New("to vertex invalid")
	}
	b.adjMatrix[from][to] = 1
	b.adjMatrix[to][from] = 1
	return nil
}

func (b *Builder) vertexIndexValid(ind int) bool {
	return ind >= 0 && ind < len(b.adjMatrix)
}
