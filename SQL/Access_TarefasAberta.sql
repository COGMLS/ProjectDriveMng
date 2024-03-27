SELECT Tarefas.*
FROM Tarefas
WHERE (((Tarefas.Status)<>"Concluído" And (Tarefas.Status)<>"Cancelado"))
ORDER BY Tarefas.Prioridade, Tarefas.Status, Tarefas.[Data de Conclusão];
