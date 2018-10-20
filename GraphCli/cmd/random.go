package cmd

import (
	"log"
	"math/rand"
	"time"

	"github.com/TheMacies/CommonSubgraph/GraphCli/graph"
	"github.com/spf13/cobra"
)

var (
	edgeProbability float64
	random          *rand.Rand
)

func init() {
	createCmd.AddCommand(randomCmd)
	randomCmd.Flags().Float64VarP(&edgeProbability, "probability", "p", 0, "probability of every edge being added")
	random = rand.New(rand.NewSource(time.Now().Unix()))
}

var randomCmd = &cobra.Command{
	Use:   "random",
	Short: "Create random graph",
	Run: func(cmd *cobra.Command, args []string) {
		g, err := graph.New(vertices)
		if err != nil {
			log.Fatalf("Error creating graph: %v", err)
		}

		if vertices > 1 {
			g.AddEdge(0, 1)
		}

		for i := 2; i < vertices; i++ {
			randPrevVertex := random.Int() % i
			g.AddEdge(i, randPrevVertex)
		}

		for i := 0; i < vertices; i++ {
			for j := i + 1; j < vertices; j++ {
				if random.Float64() < edgeProbability {
					g.AddEdge(i, j)
				}
			}
		}
		exportGraph(g)
	},
}
