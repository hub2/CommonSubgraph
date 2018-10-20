package cmd

import (
	"log"
	"os"

	"github.com/TheMacies/CommonSubgraph/GraphCli/graph"
	"github.com/spf13/cobra"
)

var (
	input string
)

func init() {
	rootCmd.AddCommand(showCmd)
	showCmd.Flags().StringVarP(&input, "input", "i", "", "path to file containing graph")
	showCmd.MarkFlagRequired("input")
}

var showCmd = &cobra.Command{
	Use:   "show",
	Short: "Show graph using graphviz",
	Run: func(cmd *cobra.Command, args []string) {
		f, err := os.Open(input)
		if err != nil {
			log.Fatalf("Could not open file: %v", err)
		}
		defer f.Close()

		g, err := graph.Import(f)
		if err != nil {
			log.Fatalf("Could not import graph: %v", err)
		}

		graph.Export(g, os.Stdout)
	},
}
