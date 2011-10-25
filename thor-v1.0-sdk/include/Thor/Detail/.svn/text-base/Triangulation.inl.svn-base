/////////////////////////////////////////////////////////////////////////////////
//
// Thor C++ Library
// Copyright (c) 2011 Jan Haller
// 
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////

namespace thor
{
namespace detail
{

	// Forward declarations
	class AdvancedTriangle;
	class AdvancedVertex;
	class AdvancedEdge;

	// Functor to compare Vertex pointers (the original instance must be kept, no copies) in std::set.
	struct THOR_API CompareRawVertexPtrs
	{
		bool operator() (const Vertex* lhs, const Vertex* rhs) const;
	};

	// The same for advanced vertices. Since AdvancedVertex is not derived from Vertex, this is necessary.
	struct THOR_API CompareVertexPtrs
	{
		bool operator() (const AdvancedVertex* lhs, const AdvancedVertex* rhs) const;
	};

	// Functor to sort constrained edges by their positions, needed to store them inside std::set.
	struct THOR_API CompareEdges
	{
		bool operator() (const AdvancedEdge& lhs, const AdvancedEdge& rhs) const;
	};

	// ---------------------------------------------------------------------------------------------------------------------------


	// Type definitions of containers
	typedef std::vector<Vertex>								VertexCtr;
	typedef std::deque<AdvancedVertex>						AdvancedVertexCtr;
	typedef std::set<const Vertex*, CompareRawVertexPtrs>	RawVertexPtrSet;
	typedef std::set<AdvancedVertex*, CompareVertexPtrs>	VertexPtrSet;
	typedef std::set<AdvancedEdge, CompareEdges>			EdgeSet; 
	typedef std::list<AdvancedTriangle>						TriangleList;

	// Type definitions of often used iterators
	typedef VertexPtrSet::iterator							VertexPtrIterator;
	typedef TriangleList::iterator							TriangleIterator;
	
	// ---------------------------------------------------------------------------------------------------------------------------


	// Circle class, needed for circumcircle
	struct Circle
	{
									Circle(sf::Vector2f midPoint, float squaredRadius);

		sf::Vector2f				midPoint;
		float						squaredRadius;
	};

	// Meta-information vertex, for algorithm internals
	class THOR_API AdvancedVertex 
	{
		public:
										AdvancedVertex(const Vertex& userVertex, TriangleIterator surroundingTriangle);
			sf::Vector2f				GetPosition() const;
			void						SetSurroundingTriangle(TriangleIterator target);
			TriangleIterator			GetSurroundingTriangle() const;
			const Vertex&				GetUserVertex() const;
		
		private:
			const Vertex*				mUserVertex;
			TriangleIterator			mSurroundingTriangle;
	};

	// Meta-information edge, for algorithm internals
	class THOR_API AdvancedEdge : public Edge<Vertex>
	{
		public:
										AdvancedEdge(const Vertex& startPoint, const Vertex& endPoint);
		
			template <typename UserVertex>
										AdvancedEdge(const Edge<UserVertex>& userEdge)
			: Edge<Vertex>(userEdge[0], userEdge[1])
			{
				OrderCorners();
			}
	
		private:
			// Sorts the corners by vector-component-sum to allow faster access inside std::set.
			void OrderCorners();
	};

	// Iterator to a triangle which can be explicitly invalid ("opt" stands for "optional").
	struct THOR_API OptTriangleIterator
	{
									OptTriangleIterator();
									OptTriangleIterator(TriangleIterator target);
									OptTriangleIterator(const OptTriangleIterator& origin);

		OptTriangleIterator&		operator= (const OptTriangleIterator& origin);

		// Members
		bool						valid;
		TriangleIterator			target;
	};

	// A triangle that carries advanced information in order to efficiently support the algorithm.
	class THOR_API AdvancedTriangle : public Triangle<Vertex>
	{	
		public:
										AdvancedTriangle(const Vertex& corner0, const Vertex& corner1, const Vertex& corner2);
		
			void						AddVertex(AdvancedVertex& vertexRef);

			void						RemoveVertex(AdvancedVertex& vertexRef);	
			void						RemoveVertex(VertexPtrIterator vertexItr);
		
			VertexPtrIterator			Begin();		
			VertexPtrIterator			End();
		
			// Sets/returns the adjacent triangle on the opposite side of the corner #index.
			void						SetAdjacentTriangle(unsigned int index, const OptTriangleIterator& adjacentTriangle);
			OptTriangleIterator			GetAdjacentTriangle(unsigned int index) const;

			// Marks this triangle (or removes mark)
			void						Flag(bool flagged = true);
			bool						IsFlagged() const;

		private:		
			VertexPtrSet							mRemainingVertices;
			std::tr1::array<OptTriangleIterator, 3>	mAdjacentTriangles;
			bool									mFlagged;
	};

	// ---------------------------------------------------------------------------------------------------------------------------


	// Function declarations
	float				THOR_API SumVectorComponents(sf::Vector2f vector);
	void 				THOR_API InsertPoint(TriangleList& triangles, AdvancedVertex& vertex, const VertexCtr& boundaryVertices, const EdgeSet& constrainedEdges);
	void 				THOR_API CreateBoundaryPoints(AdvancedVertexCtr& allVertices, VertexCtr& boundaryVertices, TriangleList& triangles);
	void 				THOR_API SetBoundaryPositions(const AdvancedVertexCtr& allVertices, VertexCtr& boundaryVertices);
	bool 				THOR_API Has1Of3Corners(const AdvancedTriangle& triangle, const VertexCtr& corners);
	bool 				THOR_API ClockwiseOrientation(sf::Vector2f v0, sf::Vector2f v1, sf::Vector2f v2);
	bool 				THOR_API IsEdgeConstrained(const EdgeSet& constrainedEdges, const Vertex& startPoint, const Vertex& endPoint);
	OptTriangleIterator THOR_API HasUnusedAdjacent(const AdvancedTriangle& triangle, unsigned int index, const VertexCtr& boundaryVertices, const EdgeSet& constrainedEdges);
	void				THOR_API RemoveOuterPolygonTriangles(TriangleList& triangles, TriangleIterator current, const EdgeSet& constrainedEdges);

	// ---------------------------------------------------------------------------------------------------------------------------


	// Policy class for small differences in triangulation - here for TriangulateConstrained()
	template <typename InputIterator>
	struct ConstrainedTrDetails
	{
		ConstrainedTrDetails(InputIterator constrainedEdgesBegin, InputIterator constrainedEdgesEnd)
		: constrainedEdgesBegin(constrainedEdgesBegin)
		, constrainedEdgesEnd(constrainedEdgesEnd)
		{
		}

		InputIterator constrainedEdgesBegin;
		InputIterator constrainedEdgesEnd;
	
		static const bool isPolygon = false;
	};

	// Policy class for small differences in triangulation - here for TriangulatePolygon() without edgesOut parameter
	struct PolygonTrDetails
	{
		static const bool isPolygon = true;
	};

	// Policy class for small differences in triangulation - here for TriangulatePolygon() with edgesOut parameter
	template <typename OutputIterator, class VertexType>
	struct PolygonOutputTrDetails
	{
		PolygonOutputTrDetails(OutputIterator edgesOut)
		: edgesOut(edgesOut)
		{
		}
	
		OutputIterator edgesOut;

		static const bool isPolygon = true;
	};

	// ---------------------------------------------------------------------------------------------------------------------------


	// Sort out vertices according to their "importance". Vertices that are part of a constrained edge shall be inserted first.
	// Adds constrained edges as well.
	template <typename InputIterator1, typename InputIterator2>
	void CollateVerticesConstrained(TriangleIterator firstTriangle, AdvancedVertexCtr& allVertices, EdgeSet& constrainedEdges,
		InputIterator1 verticesBegin, InputIterator1 verticesEnd, InputIterator2 constrainedEdgesBegin, InputIterator2 constrainedEdgesEnd)
	{
		// Sort out "important" vertices
		RawVertexPtrSet importantVertices;
		for (; constrainedEdgesBegin != constrainedEdgesEnd; ++constrainedEdgesBegin)
		{
			typedef typename std::iterator_traits<InputIterator2>::value_type UserEdge;
			const UserEdge& edge = *constrainedEdgesBegin;
		
			importantVertices.insert(&edge[0]);
			importantVertices.insert(&edge[1]);
			constrainedEdges.insert(edge);
		}
	
		// Insert important vertices, link to base triangle
		THOR_CONST_FOREACH(RawVertexPtrSet, importantVertices, itr)
		{
			allVertices.push_back(AdvancedVertex(**itr, firstTriangle));
			firstTriangle->AddVertex(allVertices.back());
		}

		// Insert other vertices, link to base triangle
		for (; verticesBegin != verticesEnd; ++verticesBegin)
		{
			const Vertex& vertex = *verticesBegin;
	
			if (importantVertices.find(&vertex) == importantVertices.end())
			{
				allVertices.push_back(detail::AdvancedVertex(vertex, firstTriangle));
				firstTriangle->AddVertex(allVertices.back());
			}
		}
	}

	// Helper function for CollateVerticesPolygon(); constructs an edge and adds it to the container and output iterator.
	inline void AddEdge(EdgeSet& constrainedEdges, const Vertex* previousVertex, const Vertex& currentVertex, const PolygonTrDetails&)
	{
		if (previousVertex != NULL)
			constrainedEdges.insert(AdvancedEdge(*previousVertex, currentVertex));
	}

	// Overload for PolygonTrDetails<OutputIterator> to write in an output iterator
	template <typename OutputIterator, class VertexType>
	void AddEdge(EdgeSet& constrainedEdges, const Vertex* previousVertex, const Vertex& currentVertex, PolygonOutputTrDetails<OutputIterator, VertexType> details)
	{
		if (previousVertex != NULL)
		{	
			*details.edgesOut++ = Edge<VertexType>(
				static_cast<const VertexType&>(*previousVertex),
				static_cast<const VertexType&>(currentVertex));
		
			constrainedEdges.insert(AdvancedEdge(*previousVertex, currentVertex));
		}
	}

	// CollateVertices Implementation for polygons
	template <typename InputIterator, class AdditionalDetails>
	void CollateVerticesPolygon(TriangleIterator firstTriangle, AdvancedVertexCtr& allVertices, EdgeSet& constrainedEdges,
		InputIterator verticesBegin, InputIterator verticesEnd, const AdditionalDetails& details)
	{
		// Empty vertex range: Do nothing
		if (verticesBegin == verticesEnd)
			return;

		const Vertex& firstVertex = *verticesBegin;
		const Vertex* previousVertex = NULL;
	
		for (; verticesBegin != verticesEnd; ++verticesBegin)
		{	
			// Add the vertex to allVertices, link with firstTriangle
			AdvancedVertex vertex(*verticesBegin, firstTriangle);
			allVertices.push_back(vertex);
			firstTriangle->AddVertex(allVertices.back()); 

			// Add edge of adjacent vertices
			AddEdge(constrainedEdges, previousVertex, vertex.GetUserVertex(), details);
			previousVertex = &vertex.GetUserVertex();
		}
	
		// If at least one vertex is contained, insert edge from last to first vertex, so that the boundary is closed.
		AddEdge(constrainedEdges, previousVertex, firstVertex, details);
	}

	// Indirect overload for ConstrainedTrDetail<InputIterator2>
	template <typename InputIterator1, typename InputIterator2>
	void CollateVertices(TriangleIterator firstTriangle, AdvancedVertexCtr& allVertices, EdgeSet& constrainedEdges,
		InputIterator1 verticesBegin, InputIterator1 verticesEnd, const ConstrainedTrDetails<InputIterator2>& details)
	{
		CollateVerticesConstrained(firstTriangle, allVertices, constrainedEdges, verticesBegin, verticesEnd,
			details.constrainedEdgesBegin, details.constrainedEdgesEnd);
	}

	// Indirect overload for PolygonTrDetails
	template <typename InputIterator>
	void CollateVertices(TriangleIterator firstTriangle, AdvancedVertexCtr& allVertices, EdgeSet& constrainedEdges,
		InputIterator verticesBegin, InputIterator verticesEnd, const PolygonTrDetails& details)
	{
		CollateVerticesPolygon(firstTriangle, allVertices, constrainedEdges, verticesBegin, verticesEnd, details);
	}

	// Indirect overload for PolygonTrDetails<OutputIterator>
	template <typename InputIterator, typename OutputIterator, class VertexType>
	void CollateVertices(TriangleIterator firstTriangle, AdvancedVertexCtr& allVertices, EdgeSet& constrainedEdges,
		InputIterator verticesBegin, InputIterator verticesEnd, const PolygonOutputTrDetails<OutputIterator, VertexType>& details)
	{
		CollateVerticesPolygon(firstTriangle, allVertices, constrainedEdges, verticesBegin, verticesEnd, details);
	}

	// Removes all triangles that are not directly required for the resulting triangulation (algorithm-supporting data).
	// In case that a polygon is triangulated, all triangles at the outside of the polygon are removed.
	template <bool LimitToPolygon>
	void RemoveUnusedTriangles(TriangleList& triangles, const VertexCtr& boundaryVertices, const EdgeSet& constrainedEdges)
	{
		for (TriangleList::iterator itr = triangles.begin(); itr != triangles.end(); )
		{
			// If the current triangle is located at the boundary (touches one of the boundary corners)
			if (Has1Of3Corners(*itr, boundaryVertices))
			{
				// When we just want to triangulate the inside of a polygon, we must cut off all outer triangles, beginning
				// at any boundary-touching triangle.
				// LimitToPolygon is a constant expression (template parameter), this might arise compiler warnings.
				if (LimitToPolygon)
					return RemoveOuterPolygonTriangles(triangles, itr, constrainedEdges);

				// Otherwise, only the very outer triangles (those touching the boundary vertices) must be removed
				else
					itr = triangles.erase(itr);
			}
		
			// Triangle is retained, continue
			else
			{
				++itr;
			}
		}
	}

	template <class VertexType, typename InputIterator, typename OutputIterator>
	OutputIterator TransformTriangles(InputIterator begin, InputIterator end, OutputIterator out)
	{
		for (; begin != end; ++begin)
		{
			const AdvancedTriangle& current = *begin;
		
			// Downcast to original vertex type (during the algorithm, we abandoned full type information)
			*out++ = Triangle<VertexType>(
				static_cast<const VertexType&>(current[0]),
				static_cast<const VertexType&>(current[1]),
				static_cast<const VertexType&>(current[2]));
		}
	
		return out;
	}

	template <typename InputIterator, typename OutputIterator, class AdditionalDetails>
	OutputIterator TriangulateImpl(InputIterator verticesBegin, InputIterator verticesEnd, OutputIterator trianglesOut, const AdditionalDetails& details)
	{
		// Create container for all vertices with additional implementation data (allVertices) and for triangles
		VertexCtr			boundaryVertices;
		AdvancedVertexCtr	allVertices;
		TriangleList		triangles;
		EdgeSet				constrainedEdges;
	
		// Avoid reallocations (and thus iterator and reference invalidations), add first three boundary (dummy, as they're removed afterwards) vertices
		CreateBoundaryPoints(allVertices, boundaryVertices, triangles);
	
		// Bring vertices in ideal order for constrained Delaunay triangulation, and add constrained edges
		CollateVertices(triangles.begin(), allVertices, constrainedEdges, verticesBegin, verticesEnd, details);

		// Set the positions of the boundary vertices, according to the spread of the internal vertices
		SetBoundaryPositions(allVertices, boundaryVertices);
	
		// Insert each vertex. This invalidates the iterator first (because the old triangle is removed (split)).
		for (AdvancedVertexCtr::iterator itr = allVertices.begin() + 3, end = allVertices.end(); itr != end; ++itr) 
			InsertPoint(triangles, *itr, boundaryVertices, constrainedEdges);
	
		// Remove triangles that are not contained in the final triangulation
		RemoveUnusedTriangles<AdditionalDetails::isPolygon>(triangles, boundaryVertices, constrainedEdges);

		// Transform from algorithm-specific data structures to user interface
		typedef typename std::iterator_traits<InputIterator>::value_type UserVertex;
		return TransformTriangles<UserVertex>(triangles.begin(), triangles.end(), trianglesOut);
	}

} // namespace detail

// ---------------------------------------------------------------------------------------------------------------------------


template <typename InputIterator, typename OutputIterator>
OutputIterator Triangulate(InputIterator verticesBegin, InputIterator verticesEnd, OutputIterator trianglesOut)
{
	// Delaunay Triangulation == Constrained Delaunay Triangulation without constraining edges
	detail::EdgeSet noEdges;
	return TriangulateConstrained(verticesBegin, verticesEnd, noEdges.begin(), noEdges.end(), trianglesOut);
}

template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
OutputIterator TriangulateConstrained(InputIterator1 verticesBegin, InputIterator1 verticesEnd,
	InputIterator2 constrainedEdgesBegin, InputIterator2 constrainedEdgesEnd, OutputIterator trianglesOut)
{
	return detail::TriangulateImpl(verticesBegin, verticesEnd, trianglesOut,
		detail::ConstrainedTrDetails<InputIterator2>(constrainedEdgesBegin, constrainedEdgesEnd));
}

template <typename InputIterator, typename OutputIterator>
OutputIterator TriangulatePolygon(InputIterator verticesBegin, InputIterator verticesEnd, OutputIterator trianglesOut)
{
	return detail::TriangulateImpl(verticesBegin, verticesEnd, trianglesOut,
		detail::PolygonTrDetails());
}

template <typename InputIterator, typename OutputIterator1, typename OutputIterator2>
OutputIterator1 TriangulatePolygon(InputIterator verticesBegin, InputIterator verticesEnd, OutputIterator1 trianglesOut, OutputIterator2 edgesOut)
{
	return detail::TriangulateImpl(verticesBegin, verticesEnd, trianglesOut, 
		detail::PolygonOutputTrDetails<OutputIterator2, typename std::iterator_traits<InputIterator>::value_type>(edgesOut));
}

template <class VertexType>
bool Intersect(const Edge<VertexType>& lhs, const Edge<VertexType>& rhs)
{
	sf::Vector2f a = lhs[0].GetPosition(); //    c
	sf::Vector2f b = lhs[1].GetPosition(); // a--+------b
	sf::Vector2f c = rhs[0].GetPosition(); //    |
	sf::Vector2f d = rhs[1].GetPosition(); //    d
	
	if (a == c || a == d || b == c || b == d)
		return false;
	
	return detail::ClockwiseOrientation(a, c, d) != detail::ClockwiseOrientation(b, c, d)
		&& detail::ClockwiseOrientation(a, b, c) != detail::ClockwiseOrientation(a, b, d);
}

} // namespace thor
