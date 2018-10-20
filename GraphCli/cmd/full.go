package cmd

import (
	"log"

	"github.com/TheMacies/CommonSubgraph/GraphCli/graph"
	"github.com/spf13/cobra"
)

func init() {
	createCmd.AddCommand(fullCmd)
}

var fullCmd = &cobra.Command{
	Use:   "full",
	Short: "Create fully connected graph",
	Run: func(cmd *cobra.Command, args []string) {
		g, err := graph.New(vertices)
		if err != nil {
			log.Fatalf("Error creating graph: %v", err)
		}
		for i := 0; i < vertices; i++ {
			for j := i + 1; j < vertices; j++ {
				err = g.AddEdge(i, j)
				if err != nil {
					log.Fatalf("Error adding edge: %v", err)
				}
			}
		}
		exportGraph(g)
	},
}
