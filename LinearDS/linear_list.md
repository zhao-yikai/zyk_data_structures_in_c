**Abstract Data Type (ADT) of a Linear List**

**Type Name**: `List`
**Data Object Set**:
A list is an ordered sequence of `n` (`n ≥ 0`) elements denoted as `(a₁, a₂, ..., aₙ)`, where:
- `a₁` is the first element (**head**).
- `aₙ` is the last element (**tail**).
- `aᵢ₊₁` is the **direct successor** of `aᵢ`.
- `aᵢ₋₁` is the **direct predecessor** of `aᵢ`.
These relationships reflect a one-to-one adjacency logic between elements.

**Operations**:
For a list `L` (of type `List`), position `i` (integer), and element `X` (of type `ElementType`), core operations include:

1. **`List MakeEmpty()`**
   Initializes a new empty list.

2. **`ElementType FindKth(List L, int i)`**
   Returns the element `aᵢ` in `L` at the specified position `i`.

3. **`Position Find(List L, ElementType X)`**
   Returns the position of the first occurrence of `X` in `L`. Returns an error if `X` is not found.

4. **`bool Insert(List L, ElementType X, int i)`**
   Inserts `X` into `L` **before** position `i`. Returns `true` on success, `false` otherwise.

5. **`bool Delete(List L, int i)`**
   Deletes the element at position `i` in `L`. Returns `true` on success, `false` otherwise.

6. **`int Length(List L)`**
   Returns the number of elements in `L`.
